#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26


void calculateLetterFrequencies(char text[], double frequencies[]) {
    int totalLetters = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            totalLetters++;
            frequencies[tolower(text[i]) - 'a']++;
        }
    }

   
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] /= totalLetters;
    }
}


void decryptText(char ciphertext[], int shift, char decrypted[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            decrypted[i] = (ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            decrypted[i] = ciphertext[i];
        }
    }
}


void letterFrequencyAttack(char ciphertext[], int numResults) {
    double englishFrequencies[ALPHABET_SIZE] = {
        0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609, 0.0697, 0.0015,
        0.0077, 0.0402, 0.0241, 0.0675, 0.0751, 0.0193, 0.0009, 0.0599, 0.0633, 0.0906,
        0.0276, 0.0098, 0.0236, 0.0015, 0.0197
    };

    int ciphertextLength = strlen(ciphertext);
    double letterFrequencies[ALPHABET_SIZE];
    char decryptedText[1000];

   
    calculateLetterFrequencies(ciphertext, letterFrequencies);

    printf("Top %d possible plaintexts:\n", numResults);

   
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        double likelihood = 0;

       
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            likelihood += englishFrequencies[i] * letterFrequencies[(i + shift) % ALPHABET_SIZE];
        }

        
        decryptText(ciphertext, shift, decryptedText);

        
        printf("%d. Likelihood: %.4f\n", shift + 1, likelihood);
        printf("   Decrypted Text: %s\n", decryptedText);

        if (shift == numResults - 1) {
            break; 
        }
    }
}

int main() {
    char ciphertext[] = "GWN GJOTM!";
    int numResults;

    printf("Enter the number of possible plaintexts to display: ");
    scanf("%d", &numResults);

    letterFrequencyAttack(ciphertext, numResults);

    return 0;
}
