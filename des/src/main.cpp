#include "des.h"

using namespace std;
int main(){

    std::string hexPlainText = getHexInput("Enter hexadecimal plain text: ");
    std::string hexKey = getHexInput("Enter 64-bit hexadecimal key: ");
    int round = getRoundsInput("Enter the number of rounds: ");
    pt = hexToBin(hexPlainText);
    string key = hexToBin(hexKey);

    generate_keys(key);

    string ct= DES(round);
    cout << "========================================================" << endl;
    cout << "Ciphertext(Hex): " << binToHex(ct) << endl;
    cout << "Ciphertext(Bin): " << ct << endl;

    // 02468aceeca86420
    // 0f1571c947d9e859
} 