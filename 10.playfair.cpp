#include <stdio.h>
#include <string.h>

void generatePlayfairMatrix(char key[], char playfairMatrix[5][5]) {
    int k, i, j;
    char usedChars[26] = {0}; 

  
    k = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (k < strlen(key)) {
                if (usedChars[key[k] - 'A'] == 0) {
                    playfairMatrix[i][j] = (key[k] == 'J') ? 'I' : key[k];
                    usedChars[key[k] - 'A'] = 1;
                    k++;
                } else {
                    k++;
                    j--;
                }
            } else {
                for (char ch = 'A'; ch <= 'Z'; ch++) {
                    if (usedChars[ch - 'A'] == 0) {
                        playfairMatrix[i][j] = (ch == 'J') ? 'I' : ch;
                        usedChars[ch - 'A'] = 1;
                        break;
                    }
                }
            }
        }
    }
}


void findPosition(char playfairMatrix[5][5], char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I';

    for (*row = 0; *row < 5; (*row)++) {
        for (*col = 0; *col < 5; (*col)++) {
            if (playfairMatrix[*row][*col] == ch) {
                return;
            }
        }
    }
}


void encryptPlayfair(char playfairMatrix[5][5], char message[]) {
    int i, len, row1, col1, row2, col2;

    len = strlen(message);

    
    if (len % 2 != 0) {
        message[len] = 'X';
        message[len + 1] = '\0';
        len++;
    }

    
    for (i = 0; i < len; i += 2) {
        findPosition(playfairMatrix, message[i], &row1, &col1);
        findPosition(playfairMatrix, message[i + 1], &row2, &col2);

        
        if (row1 == row2) {
            message[i] = playfairMatrix[row1][(col1 + 1) % 5];
            message[i + 1] = playfairMatrix[row2][(col2 + 1) % 5];
        }
       
        else if (col1 == col2) {
            message[i] = playfairMatrix[(row1 + 1) % 5][col1];
            message[i + 1] = playfairMatrix[(row2 + 1) % 5][col2];
        }
        
        else {
            message[i] = playfairMatrix[row1][col2];
            message[i + 1] = playfairMatrix[row2][col1];
        }
    }
}

int main() {
    char key[] = "MFHIJKUNOPQZVWXYELARGDSTBC";
    char playfairMatrix[5][5];
    char message[] = "MUSTSEEYOUOVERCADOGANWESTCOMINGATONCE";
    
    printf("Original Message: %s\n", message);

    
    generatePlayfairMatrix(key, playfairMatrix);

   
    encryptPlayfair(playfairMatrix, message);

    printf("Encrypted Message: %s\n", message);

    return 0;
}

