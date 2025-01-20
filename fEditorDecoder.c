#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_text>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *decoded_text = decode_text(argv[1]);
    if (decoded_text != NULL) {
        printf("%s\n", decoded_text);
        free(decoded_text);
    }

    return 0;
}