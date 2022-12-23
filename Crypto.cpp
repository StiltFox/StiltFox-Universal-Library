#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/iterhash.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/md5.h>
#include <sstream>
#include <iomanip>
#include "SFCrypto.hpp"

using namespace StiltFox::UniversalLibrary;
using namespace std;

template<typename T>
string encrypt(string data, T hasher)
{
    stringstream output;
    CryptoPP::byte* digest;

    hasher.Update((const CryptoPP::byte*)data.c_str(),data.size());
    digest = new CryptoPP::byte[hasher.DigestSize()];
    hasher.Final(digest);

    for (int i=0; i < hasher.DigestSize(); i++) output << hex << setw(2) << setfill('0') << (int)digest[i];
    delete[] digest;

    return output.str();
}

string SFCrypto::hashSha256(string data)
{
    return encrypt(data, CryptoPP::SHA256());
}

string SFCrypto::hashMd5(string data)
{
    return encrypt(data, CryptoPP::Weak1::MD5());
}