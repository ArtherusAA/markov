#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>


void print_help() {
    printf("This is supposed to be help output\n");
}

void print_error_message(const char *message) {
    printf("error: %s\n", message);
}

int main(int argc, char** argv) {
    auto inputfile = stdin;
    bool is_stdin = true;
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
    }
    if (!is_stdin)
        fclose(inputfile);
    return 0;
}
