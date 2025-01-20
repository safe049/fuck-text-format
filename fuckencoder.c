#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void encode_text(const char *text, char *binary_text) {
    while (*text) {
        sprintf(binary_text + strlen(binary_text), "%.2x", (unsigned char)*text);
        text++;
    }
}

void save_to_file(const char *binary_text, const char *filename) {
    char full_filename[256];
    strcpy(full_filename, filename);

    // 检查文件名是否以 .fuck 结尾
    size_t len = strlen(full_filename);
    if (len < 5 || strcmp(full_filename + len - 5, ".fuck") != 0) {
        strcat(full_filename, ".fuck");
    }

    FILE *file = fopen(full_filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fwrite(binary_text, 1, strlen(binary_text), file);
    fclose(file);

    printf("Text encoded and saved to %s\n", full_filename);
}

int main() {
    char text[1024];
    char binary_text[2048] = {0};
    char filename[256];

    printf("Input text to encode: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; // 去掉换行符

    encode_text(text, binary_text);

    if (binary_text[0] == '\0') {
        printf("Error: Empty binary text.\n");
        return 1;
    }

    printf("Input filename to save (do not include .fuck): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // 去掉换行符

    save_to_file(binary_text, filename);
    return 0;
}