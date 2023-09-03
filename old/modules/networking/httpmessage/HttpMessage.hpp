#ifndef StiltFox_UniversalLibrary_HttpMessage
#define StiltFox_UniversalLibrary_HttpMessage
#include <string>
#include <unordered_map>
#include <functional>

namespace StiltFox
{
    namespace UniversalLibrary
    {
        struct HttpMessage 
        {
            enum Method {GET,HEAD,POST,PUT,PATCH,DELETE,CONNECT,OPTIONS,TRACE,ERROR,NONE};
            int statusCode;
            Method httpMethod;
            std::string requestUri;
            std::string statusReason;
            std::unordered_map<std::string,std::string> headers;
            std::string body;

            HttpMessage(int statusCode, std::unordered_map<std::string,std::string> headers = {}, std::string body = "", std::string statusReason = "");
            HttpMessage(Method method, std::string uri = "*", std::unordered_map<std::string,std::string> headers = {}, std::string body = "");
            HttpMessage(int socketId, std::function<int(int,char*,int)> reader);
            
            std::string getHttpMethodAsString() const;
            std::string printAsResponse() const;
            std::string printAsRequest() const;

            bool operator==(const HttpMessage&) const;
            bool operator!=(const HttpMessage&) const;

            protected:
            std::string printBodyAndHeaders() const;
            void parseString(std::string);
        };
    }
}
#endif