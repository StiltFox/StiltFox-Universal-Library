#include <gtest/gtest.h>
#include "HttpMessage.hpp"

using namespace StiltFox::UniversalLibrary;

void PrintTo(const HttpMessage& message, std::ostream* stream)
{
    *stream << "statusCode: " << message.statusCode << std::endl
        << "httpMethod: " << message.httpMethod << std::endl
        << "requestUri: " << message.requestUri << std::endl
        << "statusReason: " << message.statusReason << std::endl
        << "body: " << message.body << std::endl << "headers: [";

        for (auto const&[key, value] : message.headers)
        {
            *stream << "\"" << key << "\": \"" << value << "\", ";
        }

        *stream << "]" << std::endl;
}

int getDataChunk(std::string wholeData, char* chunkBuffer, int chunkSize, int currentChunk)
{
    int copySize = 0;
    int currentPos = currentChunk * chunkSize;
    if (currentPos < wholeData.length())
    {
        copySize = currentPos + chunkSize > wholeData.length() ? wholeData.length() - currentPos : chunkSize;
        memcpy(chunkBuffer, wholeData.substr(currentPos, chunkSize).c_str(), copySize);
    }
    return copySize;
}

TEST(HttpMessage, printAsRequest_will_print_a_well_formed_http_request)
{
    //given we have a http message with all data needed
    HttpMessage complete(HttpMessage::GET, "/an_endpoint", {{"header","some_value"},{"header2","some_val2"}}, "this is my body");

    //when we print the http message as a  request
    std::string actual = complete.printAsRequest();

    //then we get back a well formatted request
    ASSERT_EQ(actual, "GET /an_endpoint HTTP/1.1\r\nheader2: some_val2\r\nheader: some_value\r\n\r\nthis is my body");
}

TEST(HttpMessage, printAsResponse_will_print_a_well_formatted_http_response)
{
    //given we have a http response with all the data needed
    HttpMessage complete(200, {{"header","some_value"},{"header2","some_val2"}}, "This is a body");

    //when we print the http message as a response
    std::string actual = complete.printAsResponse();

    //then we get back a well formatted response
    ASSERT_EQ(actual,"HTTP/1.1 200 OK\r\nheader2: some_val2\r\nheader: some_value\r\n\r\nThis is a body");
}

TEST(HttpMessage, reading_from_a_well_formed_socket_request_will_produce_a_well_formed_HttpMessage)
{
    //given we have a valid data stream
    std::string dataToStream = "POST /an_endpoint HTTP/1.1\r\nheader2: some_val2\r\nheader: some_value\r\n\r\nthis is my body";
    int currentChunk = 0;

    //when we read the socket, let's pretend it's 9080
    HttpMessage actual(9080,[dataToStream, &currentChunk](int socketId, char* buffer, int chunksize)
    {
        int readBytes = getDataChunk(dataToStream, buffer, chunksize, currentChunk);
        currentChunk++;
        return readBytes;
    });

    //then we get back the desired http response
    ASSERT_EQ(actual, HttpMessage(HttpMessage::POST,"/an_endpoint",{{"header2","some_val2"},{"header","some_value"}},"this is my body"));
}

TEST(HttpMessage, reading_from_a_socket_that_does_not_have_headers_or_a_body_will_parse_properly)
{
    //given we have an http request with just the meta data
    std::string dataToStream = "POST /an_endpoint HTTP/1.1";
    int currentChunk = 0;

    //when we read the socket, let's pretend it's 9080
    HttpMessage actual(9080,[dataToStream, &currentChunk](int socketId, char* buffer, int chunksize)
    {
        int readBytes = getDataChunk(dataToStream, buffer, chunksize, currentChunk);
        currentChunk++;
        return readBytes;
    });

    //then we get back the desired http response
    ASSERT_EQ(actual, HttpMessage(HttpMessage::POST, "/an_endpoint"));
}

TEST(HttpMessage, reading_from_a_socket_that_does_not_have_a_Body_will_parse_properly)
{
    //given we have an http request without a body
    std::string dataToStream = "POST /an_endpoint HTTP/1.1\r\nheader2: some_val2\r\nheader: some_value";
    int currentChunk = 0;

    //when we read the socket, let's pretend it's 9080
    HttpMessage actual(9080,[dataToStream, &currentChunk](int socketId, char* buffer, int chunksize)
    {
        int readBytes = getDataChunk(dataToStream, buffer, chunksize, currentChunk);
        currentChunk++;
        return readBytes;
    });

    //then we get back the desired http response
    ASSERT_EQ(actual, HttpMessage(HttpMessage::POST, "/an_endpoint", {{"header2","some_val2"},{"header","some_value"}}));
}

TEST(HttpMessage, reading_from_a_socket_that_does_not_have_headings_will_parse_properly)
{
    //given we have an http request without headers
    std::string dataToStream = "POST /an_endpoint HTTP/1.1\r\n\r\nThis is a body";
    int currentChunk = 0;

    //when we read the socket, let's pretend it's 9080
    HttpMessage actual(9080,[dataToStream, &currentChunk](int socketId, char* buffer, int chunksize)
    {
        int readBytes = getDataChunk(dataToStream, buffer, chunksize, currentChunk);
        currentChunk++;
        return readBytes;
    });

    //then we get back the desired http response
    ASSERT_EQ(actual, HttpMessage(HttpMessage::POST, "/an_endpoint", {}, "This is a body"));
}

TEST(HttpMessage, reading_from_a_socket_request_with_an_unknown_method_will_set_httpMethod_to_error)
{
    //given we have an http request with an unknown method
    std::string dataToStream = "PICKLE /an_endpoint HTTP/1.1\r\nheader2: some_val2\r\nheader: some_value\r\n\r\nthis is my body";
    int currentChunk = 0;

    //when we read the socket, let's pretend it's 9080
    HttpMessage actual(9080,[dataToStream, &currentChunk](int socketId, char* buffer, int chunksize)
    {
        int readBytes = getDataChunk(dataToStream, buffer, chunksize, currentChunk);
        currentChunk++;
        return readBytes;
    });

    //then we get back that the method is not allowed
    HttpMessage expectedMessage(HttpMessage::ERROR,"/an_endpoint",{{"header2","some_val2"},{"header","some_value"}},"this is my body");
    ASSERT_EQ(actual, expectedMessage);
}

TEST(HttpMessage, reading_from_a_socket_without_an_endpoint_will_finish_parsing)
{
    //given we have an http request without an endpoint
    std::string endpointMissing = "POST  HTTP/1.1\r\nheader2: some_val2\r\nheader: some_value\r\n\r\nthis is my body";
    int currentChunk = 0;

    //when we read the socket, let's pretend it's 9080
    HttpMessage actual(9080,[endpointMissing, &currentChunk](int socketId, char* buffer, int chunksize)
    {
        int readBytes = getDataChunk(endpointMissing, buffer, chunksize, currentChunk);
        currentChunk++;
        return readBytes;
    });

    //then we get back that the message is malformed
    HttpMessage expectedMessage(HttpMessage::POST,"",{{"header2","some_val2"},{"header","some_value"}},"this is my body");
    ASSERT_EQ(actual, expectedMessage);
}

TEST(HttpMessage, reading_from_a_socket_without_an_endpoint_or_space_will_finish_parsing)
{
    //given we have an http request without an endpoint
    std::string endpointMissingWithoutSpace = "POST HTTP/1.1\r\nheader2: some_val2\r\nheader: some_value\r\n\r\nthis is my body";
    int currentChunk = 0;

    //when we read the socket, let's pretend it's 9080
    HttpMessage actualNoSpace(9080,[endpointMissingWithoutSpace, &currentChunk](int socketId, char* buffer, int chunksize)
    {
        int readBytes = getDataChunk(endpointMissingWithoutSpace, buffer, chunksize, currentChunk);
        currentChunk++;
        return readBytes;
    });

    //then we get back that the message is malformed
    HttpMessage expectedMessageWithoutSpace(HttpMessage::POST,"",{{"header2","some_val2"},{"header","some_value"}},"this is my body");
    ASSERT_EQ(actualNoSpace, expectedMessageWithoutSpace);
}

TEST(HttpMessage, reading_from_an_invalid_socket_request_will_not_cause_a_seg_fault)
{
    //given we have a garbage data stream
    std::string badData = "asdlkfjwoeihghodfal n sohdfiwekladf ng;lhfpoiea;kfhoe\r\n lkasdfhoiwea";
    int currentChunk = 0;

    //when we read the socket, let's pretend it's 104
    HttpMessage actual(104,[badData, &currentChunk](int socketId, char* buffer, int chunksize)
    {
        int readBytes = getDataChunk(badData, buffer, chunksize, currentChunk);
        currentChunk++;
        return readBytes;
    });
}