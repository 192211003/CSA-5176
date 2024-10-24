#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

int charToNum(char c) { 
    return toupper(c) - 'A'; 
}

char numToChar(int num) { 
    return num + 'A'; 
}

void encryptHill(char *text, int *keyMatrix, int keySize) {
    int textLen = strlen(text);
    int encrypted[MAX_LEN] = {0};
    int i, j, k;

    for (i = 0; i < textLen; i += keySize) {
        for (j = 0; j < keySize; j++) {
            int sum = 0;
            for (k = 0; k < keySize; k++) {
                sum += keyMatrix[j * keySize + k] * charToNum(text[i + k]);
            }
            encrypted[i + j] = sum % 26;
        }
    }

    for (i = 0; i < textLen; i++) {
        text[i] = numToChar(encrypted[i]);
    }
}

int main() {
    char plaintext[MAX_LEN];
    int keySize, keyMatrix[MAX_LEN * MAX_LEN];
    int i;

    // Input the plaintext
    printf("Enter plaintext: ");
    fgets(plaintext, MAX_LEN, stdin);

    // Remove trailing newline added by fgets
    plaintext[strcspn(plaintext, "\n")] = '\0';

    // Input the key size
    printf("Enter key size: ");
    scanf("%d", &keySize);

    // Input the key matrix
    printf("Enter key matrix:\n");
    for (i = 0; i < keySize * keySize; i++) {
        scanf("%d", &keyMatrix[i]);
    }

    // Calculate the length of the plaintext
    int textLen = strlen(plaintext);

    // Padding the text if necessary
    int padding = keySize - (textLen % keySize);
    if (padding < keySize) {
        memset(plaintext + textLen, 'X', padding);  // Add padding characters
        plaintext[textLen + padding] = '\0';  // Null-terminate
    }

    // Encrypt the text using Hill cipher
    encryptHill(plaintext, keyMatrix, keySize);

    // Output the encrypted text
    printf("Encrypted text: %s\n", plaintext);

    return 0;
}

