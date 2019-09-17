#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <string>

void print_help() {
    printf("This is supposed to be help output\n");
}

void print_error_message(const char *message) {
    printf("error: %s\n", message);
}

int read_from_file(FILE *f, char *buff) {
    int n = 1024, i = 0;
    buff = malloc(sizeof(int) * n);
    buff2 = malloc(sizeof(int) * n);
    if (buff == NULL || buff2 == NULL) {
        return -1;
    }
    while (!feof(f)) {
        buff[i] = getc(f);
        i++;
        if (n - i < 3) {
            for (int j = 0; j < i; j++) {
                buff2[j] = buff[j];
            }
            free(buff);
            n *= 2;
            buff = malloc(sizeof(int) * n);
            if (buff == NULL) {
                return -1;
            }
            for (int j = 0; j < i; j++) {
                buff[j] = buff2[j];
            }
            free(buff2);
            buff2 = malloc(sizeof(int) * n);
            if (buff2 == NULL) {
                return -1;
            }
        }
    }
    free(buff2);
    buff[i] = '\0';
    return 0;
}

int main(int argc, char** argv) {
    FILE *inputfile;
    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0) {
            print_help();
            return 0;
        } else {
            FILE *f = fopen(argv[1], "r");
            if (f == NULL) {
                print_error_message("no such file");
                return 0;
            }
            inputfile = f;
            is_stdin = false;
        }
    } else {
        print_error_message("run without arguments");
        return 0;
    }
    char *buff;
    int frerror = read_from_file(inputfile, buff);
    fclose(inputfile);
    switch (frerror) {
        case -1:
            print_error_message("system does not give enough memory to contain all instructions\n");
            return 0;
            break;
        default:
            print_error_message("file reading error occured");
            return 0;
            break;
    }
    return 0;
}
