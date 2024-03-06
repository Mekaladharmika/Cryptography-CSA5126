#include <stdio.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

char encrypt(char plaintext, int a, int b) {
    if (!isalpha(plaintext)) {
        return plaintext; 
    }

   
    int offset = (isupper(plaintext) ? 'A' : 'a') - 'a';

  
    if (gcd(a, ALPHABET_SIZE) != 1) {
        printf("Error: Invalid 'a' value. It must be coprime to %d.\n", ALPHABET_SIZE);
        return plaintext; 
    }

    int ciphertext = ((a * (plaintext - offset) + b) % ALPHABET_SIZE) + offset;

    return ciphertext;
}


int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int main() {
    char plaintext[100];
    int a, b;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter value for 'a': ");
    scanf("%d", &a);

    printf("Enter value for 'b': ");
    scanf("%d", &b);

    printf("Encrypted message: ");

    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ciphertext = encrypt(plaintext[i], a, b);
        printf("%c", ciphertext);
    }

    printf("\n");

    return 0;
}
