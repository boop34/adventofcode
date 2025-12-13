#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include <windows.h>
#include <wincrypt.h>

#pragma comment(lib, "advapi32.lib")

void getMD5(HCRYPTPROV h_prov, const std::string& input, BYTE* hash) {
    HCRYPTHASH h_hash = 0;
    DWORD hash_len = 16;
    std::string result;

    if (!CryptCreateHash(h_prov, CALG_MD5, 0, 0, &h_hash)) {
        return;
    }

    if (!CryptHashData(h_hash, (BYTE*)input.c_str(), input.length(), 0)) {
        CryptDestroyHash(h_hash);
        return;
    }

    if (!CryptGetHashParam(h_hash, HP_HASHVAL, hash, &hash_len, 0)) {
        CryptDestroyHash(h_hash);
        return;
    }

    CryptDestroyHash(h_hash);
}

long long part_one(std::string& key) {
    BYTE md5_hash[16];
    HCRYPTPROV h_prov = 0;
    if (!CryptAcquireContext(&h_prov, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        return -1;
    }

    long long result = 0ll;

    while (true) {
        std::string new_key = key + std::to_string(result);
        getMD5(h_prov, new_key, md5_hash);
        if (md5_hash[0] == 0 && md5_hash[1] == 0 && (md5_hash[2] & 0xF0) == 0)  {
            CryptReleaseContext(h_prov, 0);
            return result;
        }
        result++;
    }

    CryptReleaseContext(h_prov, 0);
    return result;
}

long long part_two(std::string& key) {
    BYTE md5_hash[16];
    HCRYPTPROV h_prov = 0;
    if (!CryptAcquireContext(&h_prov, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        return -1;
    }

    long long result = 0ll;

    while (true) {
        std::string new_key = key + std::to_string(result);
        getMD5(h_prov, new_key, md5_hash);
        if (md5_hash[0] == 0 && md5_hash[1] == 0 && md5_hash[2] == 0)  {
            CryptReleaseContext(h_prov, 0);
            return result;
        }
        result++;
    }

    CryptReleaseContext(h_prov, 0);
    return result;
}

int main() {
    std::string key;
    std::ifstream input_file("day_4.in");

    std::string line;
    while (std::getline(input_file, line)) {
        key = line;
    }

    long long part_one_sol = part_one(key);
    long long part_two_sol = part_two(key);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
