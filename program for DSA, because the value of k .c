#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/bn.h>

#define MESSAGE "Hello, World!"

void handleErrors() {
    fprintf(stderr, "An error occurred\n");
    exit(1);
}

DSA* generateDSA() {
    DSA *dsa = DSA_new();
    if (!dsa)
        handleErrors();

    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *g = BN_new();

    if (!p || !q || !g)
        handleErrors();

    // Example parameters, in a real-world scenario you should use secure parameter generation
    const char *p_hex = "FDEAB8A23F51376CC9733FA7E4E4DD73A6E533E6D7FEE293A43A02A5A8E5B754E9C41AD9FFC5A6D71CCDE9EDDB7A2D03968E7D315ADC4E0B8880AE48E8B1E3148706F42AFB9F5E46C606E9D676F56B567CD6CCE82F2D9AC7F9C6C3D0A0D86B8C3DE8A2C36C68FBBD6AB23A1F09AF7981793E88AEC7F55F971E03E54E8F";
    const char *q_hex = "E1DDB756E0A6D0701F91DCA354A85827";
    const char *g_hex = "89793A45FFADA7720CAEBDCEC3F2A37D8A4B6CD517C4370903769A75A4F34B25F5EA4DA6BA9DBA29A730FE0ACDD34012A7E2DA5C3A8B3F3A3A08A5768407A43";

    BN_hex2bn(&p, p_hex);
    BN_hex2bn(&q, q_hex);
    BN_hex2bn(&g, g_hex);

    if (!DSA_set0_pqg(dsa, p, q, g))
        handleErrors();

    if (!DSA_generate_key(dsa))
        handleErrors();

    return dsa;
}

void signAndVerifyDSA(DSA *dsa, const unsigned char *msg, int msg_len) {
    unsigned char *sig = (unsigned char *)malloc(DSA_size(dsa));
    if (!sig)
        handleErrors();

    unsigned int sig_len;

    // Sign the message
    if (DSA_sign(0, msg, msg_len, sig, &sig_len, dsa) != 1)
        handleErrors();

    // Verify the signature
    if (DSA_verify(0, msg, msg_len, sig, sig_len, dsa) != 1)
        printf("Signature verification failed\n");
    else
        printf("Signature verification succeeded\n");

    free(sig);
}

int main() {
    // Generate DSA key pair
    DSA *dsa = generateDSA();

    // Sign and verify the message multiple times
    printf("Signing and verifying message multiple times:\n");
    for (int i = 0; i < 3; i++) {
        printf("Attempt %d:\n", i + 1);
        signAndVerifyDSA(dsa, (const unsigned char *)MESSAGE, strlen(MESSAGE));
    }

    DSA_free(dsa);

    return 0;
}
