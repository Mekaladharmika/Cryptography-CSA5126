#include <stdio.h>
#include <string.h>


void findPositions(char playfairMatrix[5][5], char ch, int *row, int *col) {
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (playfairMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}


void decryptPlayfair(char playfairMatrix[5][5], char code[]) {
    int i, length, row1, col1, row2, col2;
    char decrypted[1000];

    length = strlen(code);

    for (i = 0; i < length; i += 2) {
        char ch1 = code[i];
        char ch2 = code[i + 1];

        findPositions(playfairMatrix, ch1, &row1, &col1);
        findPositions(playfairMatrix, ch2, &row2, &col2);

        
        if (row1 == row2) {
            decrypted[i] = playfairMatrix[row1][(col1 - 1 + 5) % 5];
            decrypted[i + 1] = playfairMatrix[row2][(col2 - 1 + 5) % 5];
        }
      
        else if (col1 == col2) {
            decrypted[i] = playfairMatrix[(row1 - 1 + 5) % 5][col1];
            decrypted[i + 1] = playfairMatrix[(row2 - 1 + 5) % 5][col2];
        }
       
        else {
            decrypted[i] = playfairMatrix[row1][col2];
            decrypted[i + 1] = playfairMatrix[row2][col1];
        }
    }

    decrypted[length] = '\0';
    printf("Decrypted Message: %s\n", decrypted);
}

int main() {
    char key[] = "PT109";
    char playfairMatrix[5][5];
    char code[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";

    printf("Playfair Code: %s\n", code);

   
    int k = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            playfairMatrix[i][j] = key[k++];
        }
    }

    
    decryptPlayfair(playfairMatrix, code);

    return 0;
}
