#include <stdio.h>
#include <string.h>
#include <ctype.h>


void generateCipherFromKeyword(char keyword[], char cipher[]) {
    int i, j, k;
    int keywordLength = strlen(keyword);
    char keyTable[26] = {0}; 

   
    for (i = 0; i < keywordLength; i++) {
        char currentChar = toupper(keyword[i]);
        if (currentChar >= 'A' && currentChar <= 'Z' && keyTable[currentChar - 'A'] == 0) {
            keyTable[currentChar - 'A'] = 1;
            cipher[i] = currentChar;
        }
    }

    
    k = keywordLength;
    for (i = 0; i < 26; i++) {
        if (keyTable[i] == 0) {
            cipher[k++] = 'A' + i;
        }
    }

   
    cipher[k] = '\0';
}


void encryptKeywordCipher(char plaintext[], char keyword[], char ciphertext[]) {
    char cipher[26];

   
    generateCipherFromKeyword(keyword, cipher);

    int length = strlen(plaintext);
    int i;

    
    for (i = 0; i < length; i++) {
        char currentChar = plaintext[i];

        if (isalpha(currentChar)) {
           
            currentChar = toupper(currentChar);

           
            ciphertext[i] = islower(plaintext[i]) ? tolower(cipher[currentChar - 'A']) : cipher[currentChar - 'A'];
        } else {
            
            ciphertext[i] = currentChar;
        }
    }

  
    ciphertext[i] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char plaintext[] = "Hello, World!";
    char ciphertext[100];

    printf("Original Plaintext: %s\n", plaintext);

  
    encryptKeywordCipher(plaintext, keyword, ciphertext);

    printf("Encrypted Ciphertext: %s\n", ciphertext);

    return 0;
}
