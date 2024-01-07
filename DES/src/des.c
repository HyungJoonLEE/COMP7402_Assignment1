#include "des.h"


void ask_plain(char* plain) {
    printf("Enter plain text: ");
    scanf("%s", plain);
    clear_buffer();
}


void ask_hex_plain(char* hex_plain) {
    printf("Enter hexadecimal plain text: ");
    scanf("%s", hex_plain);
    clear_buffer();
}


void ask_key(char* key) {
    printf("Enter key: ");
    scanf("%s", key);
    clear_buffer();
}


void ask_hex_key(char* hex_key) {
    printf("Enter hexadecimal key: ");
    scanf("%s", hex_key);
    clear_buffer();
}


void text_to_hex(const char* text ,char* hex_text) {
    int len = strlen(text);
    for (int i = 0, j = 0; i < len; i++, j += 2) {
        sprintf(hex_text + j, "%02x", (char)(text[i]));
    }
}


void print_hex(const char* h_p, const char* h_k) {
    printf("\n");
    printf("Hex plain text: %s\n", h_p);
    printf("Hex     key   : %s\n", h_k);
}


void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void hex2bin(const char *hex, char *bin) {
    const char *mp[16] = {"0000", "0001", "0010", "0011",
                          "0100", "0101", "0110", "0111",
                          "1000", "1001", "1010", "1011",
                          "1100", "1101", "1110", "1111"};

    int len = strlen(hex);
    bin[0] = '\0'; // Initialize the bin string

    for (int i = 0; i < len; i++) {
        if (hex[i] >= '0' && hex[i] <= '9') {
            strcat(bin, mp[hex[i] - '0']);
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            strcat(bin, mp[10 + hex[i] - 'A']);
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            strcat(bin, mp[10 + hex[i] - 'a']);
        }
    }
}


char binToHexChar(const char *bin) {
    if (strcmp(bin, "0000") == 0) return '0';
    else if (strcmp(bin, "0001") == 0) return '1';
    else if (strcmp(bin, "0010") == 0) return '2';
    else if (strcmp(bin, "0011") == 0) return '3';
    else if (strcmp(bin, "0100") == 0) return '4';
    else if (strcmp(bin, "0101") == 0) return '5';
    else if (strcmp(bin, "0110") == 0) return '6';
    else if (strcmp(bin, "0111") == 0) return '7';
    else if (strcmp(bin, "1000") == 0) return '8';
    else if (strcmp(bin, "1001") == 0) return '9';
    else if (strcmp(bin, "1010") == 0) return 'A';
    else if (strcmp(bin, "1011") == 0) return 'B';
    else if (strcmp(bin, "1100") == 0) return 'C';
    else if (strcmp(bin, "1101") == 0) return 'D';
    else if (strcmp(bin, "1110") == 0) return 'E';
    else if (strcmp(bin, "1111") == 0) return 'F';
    return '?'; // Return '?' for invalid input
}


void bin2hex(const char *bin, char *hex) {
    const char *binToHexMap[16] = {
            "0", "1", "2", "3",
            "4", "5", "6", "7",
            "8", "9", "A", "B",
            "C", "D", "E", "F"
    };

    int len = strlen(bin);

    for (int i = 0; i < len; i += 4) {
        int value = 0;

        // Convert each 4-bit binary segment to decimal
        for (int j = 0; j < 4; j++) {
            value = value * 2 + (bin[i + j] - '0');
        }

        // Append the corresponding hexadecimal character
        strcat(hex, binToHexMap[value]);
    }// Null-terminate the hex string
}


int bin2dec(long long binary) {
    int decimal = 0, i = 0, remainder;

    while (binary != 0) {
        remainder = binary % 10;
        binary /= 10;
        decimal += remainder * pow(2, i);
        ++i;
    }

    return decimal;
}


void dec2bin(int num, char *binary) {
    // Temporary buffer to store binary representation
    char temp[65];
    int index = 0;

    // Edge case for zero
    if (num == 0) {
        strcpy(binary, "0");
        return;
    }

    // Convert to binary
    while (num > 0) {
        temp[index++] = (num % 2) + '0'; // Convert bit to char and store
        num /= 2;
    }
    temp[index] = '\0'; // Null-terminate the string

    // Reverse the binary string
    int len = strlen(temp);
    for (int i = 0; i < len / 2; i++) {
        char tempChar = temp[i];
        temp[i] = temp[len - i - 1];
        temp[len - i - 1] = tempChar;
    }

    // Padding to make the length a multiple of 4
    int padding = (4 - len % 4) % 4;
    for (int i = len + padding - 1; i >= padding; i--) {
        binary[i] = temp[i - padding];
    }
    for (int i = 0; i < padding; i++) {
        binary[i] = '0';
    }
    binary[len + padding] = '\0';// Re-null-terminate the string
}


void permute(char *result, const char *k, const int *arr, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = k[arr[i] - 1];
    }
    result[n] = '\0'; // Null-terminate the result
}


void shift_left(char *k, int nth_shifts) {
    int len = strlen(k);
    for (int i = 0; i < nth_shifts; i++) {
        char first = k[0];
        for (int j = 0; j < len - 1; j++) {
            k[j] = k[j + 1];
        }
        k[len - 1] = first;
    }
}


void xor(const char *a, const char *b, char *result, int length) {
    for (int i = 0; i < length; i++) {
        result[i] = (a[i] == b[i]) ? '0' : '1';
    }
    result[length] = '\0'; // Null-terminate the result
}



const char * encrypt(const char* pt, char rkb[16][48], char rk[16][48]) {
    char binary_pt[65];
    hex2bin(pt, binary_pt);

    char permuted_pt[65];
    permute(permuted_pt, binary_pt, initial_perm, 64);

    char left[33] = {0}, right[33] = {0};
    strncpy(left, permuted_pt, 32);
    strncpy(right, permuted_pt + 32, 32);
    char sbox_str[33] = {0};
    char bin_val[9] = {0};
    for (int i = 0; i < 16; i++) {
        char right_expanded[49] = {0};
        permute(right_expanded, right, exp_d, 48);

        char xor_x[49] = {0};
        xor(right_expanded, rkb[i], xor_x, 48);


        for (int j = 0; j < 8; j++) {
            char row_bits[3] = {xor_x[j * 6], xor_x[j * 6 + 5], 0};
            char col_bits[5] = {xor_x[j * 6 + 1], xor_x[j * 6 + 2], xor_x[j * 6 + 3], xor_x[j * 6 + 4], '\0'};

            int row = bin2dec(atoll(row_bits));
            int col = bin2dec(atoll(col_bits));
            int val = sbox[j][row][col];

            dec2bin(val, bin_val);

            strcat(sbox_str, bin_val);
            memset(bin_val, 0, 9);

        }

        char permuted_sbox_str[33] = {0};
        permute(permuted_sbox_str, sbox_str, per, 32);

        char result[33] = {0};
        xor(permuted_sbox_str, left, result, 32);
        strcpy(left, result);

        if (i != 15) {
            char temp[33] = {0};
            strcpy(temp, left);
            strcpy(left, right);
            strcpy(right, temp);
        }
        char ls[33] = {0};
        char rs[33] = {0};
        char rk_str[49] = {0};
        bin2hex(left, ls);
        bin2hex(right, rs);
        strcpy(rk_str, *rk + (49 * i));
        printf("Round %d: %s %s %s\n", i + 1, ls, rs, rk_str);
        memset(sbox_str, 0, 33);
        memset(result, 0, 33);
        memset(rk_str, 0, 49);
    }

    char combined[65] = {0};
    char cipher_text[65] = {0};
    strcpy(combined, left);
    strcat(combined, right);
    memset(left, 0, 33);
    memset(right, 0, 33);

    permute(cipher_text, combined, final_perm, 64);
    printf("Cipher Text: %s\n", cipher_text);
}


void key_generation(char* key, char rkb[16][49], char rk[16][49]) {
    char permuted_key[57];
    permute(permuted_key, key, keyp, 56);

    char left[29], right[29];
    strncpy(left, permuted_key, 28);
    left[28] = '\0';
    strncpy(right, permuted_key + 28, 28);
    right[28] = '\0';

    for (int i = 0; i < 16; i++) {
        shift_left(left, shift_table[i]);
        shift_left(right, shift_table[i]);

        char combined[57];
        strcpy(combined, left);
        strcat(combined, right);

        char round_key[49];
        permute(round_key, combined, key_comp, 48);

        strcpy(rkb[i], round_key);
        bin2hex(round_key, rk[i]);
    }
}

