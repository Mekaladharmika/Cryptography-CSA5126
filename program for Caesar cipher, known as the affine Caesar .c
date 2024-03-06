#include <stdio.h>

int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

int encrypt(int a, int b, int p) {
    return (a * p + b) % 26;
}

int decrypt(int a, int b, int c) {
    int a_inverse = modInverse(a, 26);
    int p = (a_inverse * (c - b + 26)) % 26;
    return p;
}

int main() {
    int a, b, p, c;
    
    printf("Enter the values of a and b for encryption (e.g., a=3, b=7): ");
    scanf("%d,%d", &a, &b);
    
    if (gcd(a, 26) != 1) {
        printf("Invalid 'a' value. It must be coprime with 26.\n");
        return 1;
    }
    
    printf("Enter the plaintext letter (a value between 0 and 25): ");
    scanf("%d", &p);
    
    if (p < 0 || p > 25) {
        printf("Invalid plaintext value. It must be between 0 and 25.\n");
        return 1;
    }
    
    c = encrypt(a, b, p);
    printf("Encrypted letter: %c\n", 'A' + c);

    int decrypted_p = decrypt(a, b, c);
    printf("Decrypted letter: %c\n", 'A' + decrypted_p);
    
    return 0;
}
