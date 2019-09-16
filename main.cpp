#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>


void print_help() {
    printf("This is supposed to be help output\n");
}

void print_error_message(char *message) {
    printf("error: %s\n", message);
}

int main(int argc, char** argv) {
    auto inputfile = stdin;
    if (argc > 0) {
        if (strcmp(argv[0], "-h") == 0) {
            print_help();
            return 0;
        } else {
            FILE *f = open(argv[0], "r");
            if (f == NULL) {
                print_error_message("no such file");
                return 0;
            }
            inputfile = f;
        }
    }
    fclose(f);
    return 0;
}
