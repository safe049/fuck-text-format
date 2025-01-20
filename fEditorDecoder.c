#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 过滤掉非十六进制字符的函数
char *filter_binary_text(const char *input) {
    int len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (isxdigit((unsigned char)input[i])) {  // 仅保留十六进制字符
            result[index++] = input[i];
        }
    }
    result[index] = '\0';
    return result;
}


char *decode_text(const char *binary_text) {
    // 先过滤输入的 binary_text
    char *filtered_text = filter_binary_text(binary_text);
    if (filtered_text == NULL) {
        return NULL;
    }
    int length = strlen(filtered_text);
    if (length % 2!= 0) {
        printf("Decoding error: Invalid binary text length.\n");
        free(filtered_text);
        return NULL;
    }
    int text_length = length / 2;

    char *text = (char *)malloc(text_length + 1);
    if (text == NULL) {
        perror("Memory allocation failed");
        free(filtered_text);
        return NULL;
    }

    for (int i = 0; i < text_length; i++) {
        char hex[3];
        hex[0] = filtered_text[2 * i];
        hex[1] = filtered_text[2 * i + 1];
        hex[2] = '\0';

        if (strspn(hex, "0123456789abcdefABCDEF")!= 2) {
            printf("Decoding error: Invalid hexadecimal sequence '%s'.\n", hex);
            free(text);
            free(filtered_text);
            return NULL;
        }

        unsigned int byte = strtol(hex, NULL, 16);
        text[i] = (char)byte;
    }
    text[text_length] = '\0';
    free(filtered_text);
    return text;
}


int main(int argc, char *argv[]) {
    if (argc!= 2) {
        fprintf(stderr, "Usage: %s <binary_text>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *decoded_text = decode_text(argv[1]);
    if (decoded_text!= NULL) {
        printf("%s\n", decoded_text);
        free(decoded_text);
    }

    return 0;
}
