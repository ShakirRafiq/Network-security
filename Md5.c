#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

void computeMD5(const char *str, unsigned char hash[MD5_DIGEST_LENGTH]) {
    MD5((unsigned char*)str, strlen(str), hash);
}

void printMD5(unsigned char hash[MD5_DIGEST_LENGTH]) {
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char input[256];
    unsigned char hash[MD5_DIGEST_LENGTH];

    printf("Enter a string: ");
    scanf("%255s", input);

    computeMD5(input, hash);

    printf("MD5 Hash: ");
    printMD5(hash);

    return 0;
}
