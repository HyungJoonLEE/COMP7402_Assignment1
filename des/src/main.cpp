#include "des.h"

int main() {
    string txt;
    string hexPlainText = getHexInput("Enter hexadecimal plain text: ");
    string hexKey = getHexInput("Enter 64-bit hexadecimal key: ");
    int round = getRoundsInput("Enter the number of rounds: ");
    pt = hexToBin(hexPlainText);
    string key = hexToBin(hexKey);

    generate_keys(key);

    string ct= DES(round);
    cout << "================================================================" << endl;
    cout << "Ciphertext(Hex): " << binToHex(ct) << endl;
    cout << "Ciphertext(Bin): " << ct << endl;

    txt += "================================================================\n"
           "Ciphertext(Hex): " + binToHex(ct) + "\n" +
            "Ciphertext(Bin): " + ct + "\n\n";

    appendToFile("des.txt", txt);
    // 02468aceeca86420
    // 0f1571c947d9e859
} 