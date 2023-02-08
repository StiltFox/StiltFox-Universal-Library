#include <gtest/gtest.h>
#include "SFCrypto.hpp"

using namespace StiltFox::UniversalLibrary::SFCrypto;

TEST(CRYPTO, hashSha256_returns_the_hash_of_the_data_passed_in)
{
    //given we have a string to take the sha value of
    std::string toHash = "SCP-049 would like to be let in on the festivities";

    //when we take the hash of the string
    std::string hash = hashSha256(toHash);

    //then we get back the hash of the data
    ASSERT_EQ(hash, "c386fab497743e56f8b2a6df12d3839050ea31859f1479d7938435480c547d4c");
}

TEST(CRYPTO, hashMd5_returns_the_hash_of_the_data_passed_in)
{
    //given we have a string to take the sha value of
    std::string toHash = "SCP-049 would like to be let in on the festivities";

    //when we take the hash of the string
    std::string hash = hashMd5(toHash);

    //then we get back the hash of the data
    ASSERT_EQ(hash, "c93afd2d417699aa996c56e1842544ad");
}