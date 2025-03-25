#include <stdio.h>
#include <ctype.h>

void caesarCipher(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        if (isalpha(ch)) { // Check if it's a letter
            char base = isupper(ch) ? 'A' : 'a';
            text[i] = (ch - base + shift) % 26 + base;
        }
    }
}

int main() {
    char text[] = "Hello, World!";
    int shift = 3;

    caesarCipher(text, shift);
    printf("Encrypted: %s\n", text);

    return 0;
}
