#include <stdio.h>
#include <string.h>
#include <ctype.h>
char decryptChar(char ciphertext, int a_inv, int b_inv) {
    if (!isalpha(ciphertext))
        return ciphertext;
    char base = isupper(ciphertext) ? 'A' : 'a';
    int decrypted_char = (a_inv * (ciphertext - base - b_inv) % 26 + 26) % 26; 
    return decrypted_char + base; 
}
void decryptText(char *ciphertext, int a_inv, int b_inv) {
    int ciphertext_len = strlen(ciphertext);
    int i;
    for (i = 0; i < ciphertext_len; ++i) {
        ciphertext[i] = decryptChar(ciphertext[i], a_inv, b_inv);
    }
}

int main() {
    char ciphertext[100];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    int freq[26] = {0};
    int i;
    for (i = 0; ciphertext[i] != '\0'; ++i) {
        if (isalpha(ciphertext[i])) {
            int index = toupper(ciphertext[i]) - 'A';
            freq[index]++;
        }
    }
    int max_freq = 0, second_max_freq = 0, max_index = 0, second_max_index = 0;
    for ( i = 0; i < 26; ++i) {
        if (freq[i] > max_freq) {
            second_max_freq = max_freq;
            second_max_index = max_index;
            max_freq = freq[i];
            max_index = i;
        } else if (freq[i] > second_max_freq) {
            second_max_freq = freq[i];
            second_max_index = i;
        }
    }
    int a = (second_max_index - max_index + 26) % 26;
    int b = ((max_index - ('E' - 'A') * a) % 26 + 26) % 26;
    int a_inv = -1;
    for ( i = 1; i < 26; ++i) {
        if ((a * i) % 26 == 1) {
            a_inv = i;
            break;
        }
    }
    if (a_inv != -1) {
        decryptText(ciphertext, a_inv, b);
        printf("Decrypted text: %s\n", ciphertext);
    } else {
        printf("Decryption failed. The value of 'a' does not have a modular multiplicative inverse.\n");
    }
    
    return 0;
}
