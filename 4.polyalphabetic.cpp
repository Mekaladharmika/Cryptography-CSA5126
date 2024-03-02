#include <stdio.h>
#include <string.h>
#include <ctype.h>


void vigenereEncrypt(char plaintext[], char key[], char ciphertext[]) {
    int i, j, keyLength, textLength;

    keyLength = strlen(key);
    textLength = strlen(plaintext);

   
    for (i = 0, j = 0; i < textLength; i++) {
        char currentChar = plaintext[i];

        if (isalpha(currentChar)) {
            
            currentChar = toupper(currentChar);

           
            ciphertext[i] = ((currentChar - 'A') + (key[j] - 'A')) % 26 + 'A';

            
            j = (j + 1) % keyLength;
        } else {
            
            ciphertext[i] = currentChar;
        }
    }

    
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[1000];
    char key[100];
    char ciphertext[1000];

    
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    
    plaintext[strcspn(plaintext, "\n")] = 0;

    
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

   
    key[strcspn(key, "\n")] = 0;

  
    vigenereEncrypt(plaintext, key, ciphertext);

   
    printf("Encrypted Text: %s\n", ciphertext);

    return 0;
}

