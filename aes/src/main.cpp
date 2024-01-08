#include "aes.h"


vector<unsigned char> hexStringToUCharArray(const std::string& hexStr) {
    if (hexStr.length() % 2 != 0) {
        throw std::invalid_argument("Hexadecimal string length must be even.");
    }

    std::vector<unsigned char> ucharArray;
    for (size_t i = 0; i < hexStr.length(); i += 2) {
        std::string byteString = hexStr.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(std::stoul(byteString, nullptr, 16));
        ucharArray.push_back(byte);
    }

    return ucharArray;
}


int main() {
//    string plains = "0123456789abcdeffedcba9876543210";
//    string keys   = "0f1571c947d9e8590cb7add6af7f6798";
    vector<unsigned char> plain;
    vector<unsigned char> key;

    AES aes(AESKeyLength::AES_128); //// 128 - key length, can be 128, 192 or 256
    string plains = aes.getHexInput("Enter hexadecimal plain text: ");
    string keys = aes.getHexInput("Enter 64-bit hexadecimal key: ");
    int round = aes.getRoundsInput("Enter the number of rounds: ");


    plain = hexStringToUCharArray(plains);
    key = hexStringToUCharArray(keys);

    string ct = aes.vectorToString(aes.EncryptECB(plain, key, round));
    cout << "Cipher Text(Hex): " << ct << endl;
    cout << "Cipher Text(Bin): " << aes.hexToBin(ct) << endl;
}