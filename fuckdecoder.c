#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *read_from_file(const char *filename) {
    if (strlen(filename) < 5 || strcmp(filename + strlen(filename) - 5, ".fuck") != 0) {
        printf("Error: The filename must end with .fuck\n");
        return NULL;
    }

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("File read error");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *binary_text = malloc(size + 1);
    if (binary_text == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    fread(binary_text, 1, size, file);
    binary_text[size] = '\0';
    fclose(file);

    return binary_text;
}

char *decode_text(const char *binary_text) {
    int length = strlen(binary_text);
    if (length % 2 != 0) {
        printf("Decoding error: Invalid binary text length.\n");
        return NULL;
    }
    int text_length = length / 2;

    char *text = malloc(text_length + 1);
    if (text == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    for (int i = 0; i < text_length; i++) {
        char hex[3];
        hex[0] = binary_text[2*i];
        hex[1] = binary_text[2*i + 1];
        hex[2] = '\0';

        if (strspn(hex, "0123456789abcdefABCDEF") != 2) {
            printf("Decoding error: Invalid hexadecimal sequence '%s'.\n", hex);
            free(text);
            return NULL;
        }

        unsigned int byte = strtol(hex, NULL, 16);
        text[i] = (char)byte;
    }
    text[text_length] = '\0';

    return text;
}


int main() {
    char filename[256];

    printf("Enter the filename to decode (including extension .fuck): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    char *binary_text = read_from_file(filename);
    if (binary_text == NULL) {
        return 1;
    }

    char *text = decode_text(binary_text);
    free(binary_text);

    if (text == NULL) {
        return 1;
    }

    printf("Decoded text: %s\n", text);
    free(text);

    return 0;
}