#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 5

char keySquare[SIZE][SIZE];

// Function to remove duplicate letters and prepare the key square
void prepareKeySquare(char key[]) {
    int flag[26] = {0};
    int x = 0, y = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'

        if (!flag[ch - 'A']) {
            keySquare[x][y++] = ch;
            flag[ch - 'A'] = 1;
            if (y == SIZE) { y = 0; x++; }
        }
    }

    // Fill the rest with remaining letters
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!flag[ch - 'A']) {
            keySquare[x][y++] = ch;
            flag[ch - 'A'] = 1;
            if (y == SIZE) { y = 0; x++; }
        }
    }
}

// Function to find the position of a letter in the key square
void findPosition(char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keySquare[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt the text using Playfair cipher
void playfairEncrypt(char text[]) {
    int len = strlen(text);

    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        findPosition(text[i], &row1, &col1);
        findPosition(text[i + 1], &row2, &col2);

        if (row1 == row2) { // Same row
            text[i] = keySquare[row1][(col1 + 1) % SIZE];
            text[i + 1] = keySquare[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) { // Same column
            text[i] = keySquare[(row1 + 1) % SIZE][col1];
            text[i + 1] = keySquare[(row2 + 1) % SIZE][col2];
        } else { // Rectangle swap
            text[i] = keySquare[row1][col2];
            text[i + 1] = keySquare[row2][col1];
        }
    }
}

int main() {
    char key[] = "KEYWORD";
    char text[] = "HELLO";

    // Convert text to uppercase and insert 'X' for repeated letters
    char formattedText[100];
    int j = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        formattedText[j++] = toupper(text[i]);
        if (toupper(text[i]) == toupper(text[i + 1])) {
            formattedText[j++] = 'X'; // Insert 'X' if letters are the same
        }
    }
    formattedText[j] = '\0';
    if (strlen(formattedText) % 2 != 0) {
        strcat(formattedText, "X"); // Ensure even length
    }

    prepareKeySquare(key);
    playfairEncrypt(formattedText);

    printf("Encrypted: %s\n", formattedText);
    return 0;
}
