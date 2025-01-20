#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encode_text(const char *text, char *binary_text) {
    while (*text) {
        sprintf(binary_text + strlen(binary_text), "%.2x", (unsigned char)*text);
        text++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *encoded_text = malloc(2 * strlen(argv[1]) + 1);
    if (encoded_text == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    encode_text(argv[1], encoded_text);
    printf("%s\n", encoded_text);
    free(encoded_text);

    return 0;
}