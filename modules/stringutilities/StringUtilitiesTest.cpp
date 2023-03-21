#include <gtest/gtest.h>
#include "StringUtilities.hpp"

using namespace StiltFox::UniversalLibrary::StringUtilities;

TEST(StringManip, parseLine_can_parse_out_a_line_from_the_string_linux)
{
    //given we have a string
    std::string toParse = "here's a line\notherLine";
    std::string toParseEmpty = "\n";

    //when we parse the string
    std::string actual = parseLine(toParse);

    //then we get back the first line
    ASSERT_EQ(actual,"here's a line");
}

TEST(StringManip, parseLine_can_parse_out_a_line_from_the_string_windows)
{
    //given we have a string
    std::string toParse = "here's a line\r\notherLine";

    //when we parse the string
    std::string actual = parseLine(toParse);

    //then we get back the first line
    ASSERT_EQ(actual,"here's a line");
}

TEST(StringManip, parseLine_can_parse_out_a_line_from_the_string_mac)
{
    //given we have a string
    std::string toParse = "here's a line\rmac sucks";

    //when we parse the string
    std::string actual = parseLine(toParse);

    //then we get back the first line
    ASSERT_EQ(actual,"here's a line");
}

TEST(StringManip, parseLine_will_return_empty_string_when_just_a_newline_is_present)
{
    //given we have an empty line
    std::string toParse = "\n";

    //when we parse the string
    std::string actual = parseLine(toParse);

    //then we get back empty string
    ASSERT_EQ(actual,"");
}

TEST(StringManip, parseLine_will_return_whole_string_if_no_newline_present)
{
    //given we have a string with no new line
    std::string toParse = "this is a line with no line breaks. pretty long if you ask me.";

    //when we parse the string
    std::string actual = parseLine(toParse);

    //then we get back the whole string
    ASSERT_EQ(actual,"this is a line with no line breaks. pretty long if you ask me.");
}

TEST(StringManip, parseToDelim_will_return_the_part_of_the_string_before_the_deliminator)
{
    //given we have a string with a deliminator
    std::string toParse = "some:data";

    //when we parse the string
    std::string actual = parseToDelim(toParse,":");

    //then we get back 
    ASSERT_EQ(actual, "some");
}

TEST(StringManip, parseToDelim_will_return_empty_string_if_deliminator_is_only_thing_in_string)
{
    //given we have a string with a deliminator and nothing else
    std::string toParse = ":";

    //when we parse the string
    std::string actual = parseToDelim(toParse,":");

    //then we get back an empty string
    ASSERT_EQ(actual, "");
}

TEST(StringManip, parseToDelim_will_return_whole_string_if_deliminator_is_not_found)
{
    //given we have a string with no deliminator
    std::string toParse = "some:value";

    //when we parse the string
    std::string actual = parseToDelim(toParse,"-");

    //then we get back the whole string
    ASSERT_EQ(actual, "some:value");
}

TEST(StringManip, parseMap_will_parse_a_properly_deliminated_map)
{
    //given we have a string with a parsable map
    std::string toParse = "pickle: sandwitch;portal: to nowhere; ultra safe\nlines: factory\tcharacters;";

    //when we parse the string
    std::unordered_map<std::string,std::string> actual = parseMap(toParse, ": ", ";");

    //then we get back a map of strings
    ASSERT_EQ(actual,(std::unordered_map<std::string,std::string>{{"pickle", "sandwitch"},{"portal","to nowhere"},{" ultra safe\nlines", "factory\tcharacters"}}));
}