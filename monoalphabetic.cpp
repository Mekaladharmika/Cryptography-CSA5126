#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26


void monoalphabeticSubstitution(char message[], char key[]) {
  
    int length = strlen(message);
    int i;
    
    for (i = 0; i < length; ++i) {
        char ch = message[i];

        
        if (isalpha(ch)) {
            
            int index = (int)(tolower(ch) - 'a');

           
            if (isupper(ch)) {
                message[i] = toupper(key[index]);
            } else {
                message[i] = key[index];
            }
        }
    }
}

int main() {
    char message[100];
    char key[ALPHABET_SIZE + 1]; 


    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);

   
    printf("Enter the key (26 unique letters): ");
    fgets(key, sizeof(key), stdin);

   
    message[strcspn(message, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

   
    if (strlen(key) != ALPHABET_SIZE) {
        printf("Invalid key! Key must contain 26 unique letters.\n");
        return 1;
    }

 
    monoalphabeticSubstitution(message, key);

  
    printf("Encrypted message: %s\n", message);

    return 0;
}
