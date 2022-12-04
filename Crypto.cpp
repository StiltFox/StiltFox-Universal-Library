#include <openssl/evp.h>
#include <sstream>
#include <iomanip>
#include "crypto.hpp"

using namespace StiltFox::UniversalLibrary;
using namespace std;

string encrypt(string data, const EVP_MD* (*evpProvider)())
{
    stringstream ss;
    EVP_MD_CTX * evp = EVP_MD_CTX_new();

    if (evp != NULL)
    {
        if (EVP_DigestInit_ex(evp, evpProvider(), NULL))
        {
            if(EVP_DigestUpdate(evp, data.c_str(), data.size()))
            {
                unsigned char hash[EVP_MAX_MD_SIZE];
                unsigned int lengthOfHash = 0;

                if(EVP_DigestFinal_ex(evp, hash, &lengthOfHash))
                {
                    for(unsigned int i = 0; i < lengthOfHash; ++i)
                    {
                        ss << hex << setw(2) << setfill('0') << (int)hash[i];
                    }
                }
            }
        }
        EVP_MD_CTX_free(evp);
    }

    return ss.str();
}

string Crypto::hashSha256(string data)
{
    return encrypt(data, &EVP_sha256);
}

string Crypto::hashMd5(string data)
{
    return encrypt(data, &EVP_md5);
}