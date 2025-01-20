#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *decode_text(const char *binary_text) {
    int length = strlen(binary_text);
    if (length % 2 != 0) {
        fprintf(stderr, "Decoding error: Invalid binary text length.\n");
        return NULL;
    }
    int text_length = length / 2;

    char *text = malloc(text_length + 1);
    if (text == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    for (int i = 0; i < text_length; i++) {
        sscanf(binary_text + 2 * i, "%2hhx", (unsigned char *)&text[i]);
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