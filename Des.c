#include <stdio.h>
#include <string.h>

#define KEY_SIZE 64
#define SUBKEY_SIZE 48

// Permutation Choice 1 (PC-1) Table: 64-bit key -> 56-bit key
int PC1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// Permutation Choice 2 (PC-2) Table: 56-bit -> 48-bit subkey
int PC2[] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

// Number of left shifts per round
int shift_schedule[] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

// Function to apply permutation
void permute(int *table, int size, unsigned long long input, int inputSize, unsigned long long *output) {
    *output = 0;
    for (int i = 0; i < size; i++) {
        *output <<= 1;
        *output |= (input >> (inputSize - table[i])) & 1;
    }
}

// Function to perform left circular shift
unsigned int leftShift(unsigned int half, int shifts) {
    return ((half << shifts) | (half >> (28 - shifts))) & 0xFFFFFFF;
}

// Function to generate 16 subkeys
void generateKeys(unsigned long long key, unsigned long long subkeys[16]) {
    unsigned long long permutedKey;
    permute(PC1, 56, key, 64, &permutedKey);

    unsigned int C = (permutedKey >> 28) & 0xFFFFFFF;
    unsigned int D = permutedKey & 0xFFFFFFF;

    for (int i = 0; i < 16; i++) {
        C = leftShift(C, shift_schedule[i]);
        D = leftShift(D, shift_schedule[i]);

        unsigned long long combinedKey = ((unsigned long long)C << 28) | D;
        permute(PC2, 48, combinedKey, 56, &subkeys[i]);
    }
}

int main() {
    unsigned long long key = 0x133457799BBCDFF1;  // Example 64-bit key
    unsigned long long subkeys[16];

    generateKeys(key, subkeys);

    printf("Generated Subkeys:\n");
    for (int i = 0; i < 16; i++) {
        printf("Round %2d: %012llX\n", i + 1, subkeys[i]);
    }

    return 0;
}
