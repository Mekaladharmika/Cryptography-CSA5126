#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26


void encryptHillCipher(char message[], int keyMatrix[][2]) {
    int len = strlen(message);
    int encrypted[len];

    for (int i = 0; i < len; i += 2) {
        
        int p1 = toupper(message[i]) - 'A';
        int p2 = (i + 1 < len) ? toupper(message[i + 1]) - 'A' : 0;

         
        encrypted[i] = (keyMatrix[0][0] * p1 + keyMatrix[0][1] * p2) % MOD;
        encrypted[i + 1] = (keyMatrix[1][0] * p1 + keyMatrix[1][1] * p2) % MOD;
    }

    
    for (int i = 0; i < len; i++) {
        message[i] = (isupper(message[i])) ? (char)(encrypted[i] + 'A') : message[i];
    }
}


int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}


void decryptHillCipher(char message[], int keyMatrix[][2]) {
    int det = (keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]) % MOD;

    
    det = (det + MOD) % MOD;

   
    int detInverse = modInverse(det, MOD);

   
    int adjugate[2][2] = {
        {keyMatrix[1][1], -keyMatrix[0][1]},
        {-keyMatrix[1][0], keyMatrix[0][0]}
    };

   
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            adjugate[i][j] = (adjugate[i][j] * detInverse) % MOD;
            if (adjugate[i][j] < 0) {
                adjugate[i][j] += MOD;
            }
        }
    }

    int len = strlen(message);
    int decrypted[len];

    for (int i = 0; i < len; i += 2) {
     
        int c1 = toupper(message[i]) - 'A';
        int c2 = (i + 1 < len) ? toupper(message[i + 1]) - 'A' : 0;

        
        decrypted[i] = (adjugate[0][0] * c1 + adjugate[0][1] * c2) % MOD;
        decrypted[i + 1] = (adjugate[1][0] * c1 + adjugate[1][1] * c2) % MOD;
    }

   
    for (int i = 0; i < len; i++) {
        message[i] = (isupper(message[i])) ? (char)(decrypted[i] + 'A') : message[i];
    }
}

int main() {
    
    int keyMatrix[2][2] = {{9, 4}, {5, 7}};

    
    char message[] = "meet me at the usual place at ten rather than eight oclock";

    printf("Original Message: %s\n", message);

    
    encryptHillCipher(message, keyMatrix);

    printf("Encrypted Message: %s\n", message);

   
    decryptHillCipher(message, keyMatrix);

    printf("Decrypted Message: %s\n", message);

    return 0;
}
