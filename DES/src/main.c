#include "des.h"

int main(int argc, char* argv[]) {
//    char flag;
//    int round;
//    char plain[P_LEN] = {0}, key[K_LEN] = {0};
//    char hex_plain[HP_LEN] = {0}, hex_key[HK_LEN] = {0};
//
//    while(1) {
//        printf("If you know hex value, type 'y' else 'n': ");
//        scanf("%c", &flag);
//        if (flag == 'y' || flag == 'Y') {
//            ask_hex_plain(hex_plain);
//            ask_hex_key(hex_key);
//            clear_buffer();
//            break;
//        }
//        else if (flag == 'n' || flag == 'N') {
//            ask_plain(plain);
//            ask_key(key);
//            text_to_hex(plain, hex_plain);
//            text_to_hex(key, hex_key);
//            print_hex(hex_plain, hex_key);
//            clear_buffer();
//            break;
//        }
//        else {
//            clear_buffer();
//        }
//    }
//
//    printf("How many round(s) for DES: ");
//    scanf("%d", &round);
//    clear_buffer();

    char pt[] = "02468aceeca86420";
    char key[] = "0f1571c947d9e859";
    char result[57] = {0};
    char combine_str[57] = {0};
    char round_key[57] = {0};

    char binary_key[65];
    hex2bin(key, binary_key);

    permute(result, binary_key, keyp, 56);

    char left[29] = {0};
    char right[29] = {0};
    strncpy(left, result, 28);
    strncpy(right, result + 28, 28);


    char rkb[16][49] = {0};
    char rk[16][49] = {0};

    for (int i = 0; i < 16; i++) {
        shift_left(left, shift_table[i]);
        shift_left(right, shift_table[i]);
        strcat(combine_str, left);
        strcat(combine_str, right);
        permute(round_key, combine_str, key_comp, 48);
        permute(round_key, combine_str, key_comp, 48);
        memset(combine_str, 0, 57);
        strcpy(rkb[i], round_key);
        bin2hex(round_key, rk[i]);
    }


    printf("Encryption\n");
    char cipher_text[65] = {0};
    bin2hex(cipher_text, encrypt(pt, rkb, &rk));  // Adjusted to use return value of encrypt
//    char hex_cipher_text[17];
//    bin2hex(cipher_text, hex_cipher_text);
//    printf("Cipher Text: %s\n", cipher_text);
}
