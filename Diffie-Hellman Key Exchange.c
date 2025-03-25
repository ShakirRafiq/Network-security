#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute (base^exp) % mod using modular exponentiation
long long powerMod(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {  // If exponent is odd
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long p = 23; // Public prime number
    long long g = 5;  // Public base

    long long privateAlice = 6; // Alice's private key
    long long privateBob = 15;  // Bob's private key

    // Compute public keys
    long long publicAlice = powerMod(g, privateAlice, p);
    long long publicBob = powerMod(g, privateBob, p);

    // Compute shared secret keys
    long long sharedSecretAlice = powerMod(publicBob, privateAlice, p);
    long long sharedSecretBob = powerMod(publicAlice, privateBob, p);

    printf("Public Parameters: p = %lld, g = %lld\n", p, g);
    printf("Alice's Private Key: %lld\n", privateAlice);
    printf("Bob's Private Key: %lld\n", privateBob);
    printf("Alice's Public Key: %lld\n", publicAlice);
    printf("Bob's Public Key: %lld\n", publicBob);
    printf("Shared Secret Computed by Alice: %lld\n", sharedSecretAlice);
    printf("Shared Secret Computed by Bob: %lld\n", sharedSecretBob);

    return 0;
}
