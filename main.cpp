#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

void print_help() {
    printf("This is supposed to be help output\n");
}

void print_error_message(const char *message) {
    printf("error: %s\n", message);
}

int read_from_file(FILE *f, char* &buff) {
    int n = 1024, i = 0;
    buff = (char*)malloc(sizeof(int) * n);
    char *buff2 = (char*)malloc(sizeof(int) * n);
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
            buff = (char*)malloc(sizeof(int) * n);
            if (buff == NULL) {
                return -1;
            }
            for (int j = 0; j < i; j++) {
                buff[j] = buff2[j];
            }
            free(buff2);
            buff2 = (char*)malloc(sizeof(int) * n);
            if (buff2 == NULL) {
                return -1;
            }
        }
    }
    free(buff2);
    buff[i - 1] = '\0';
    return 0;
}

int parse(char *buff, std::vector <std::string> &subs, std::vector <int> &is_term) {
    int flag = 1;
    int opened_q = 0;
    int i = 0;
    int str_counter = 0;
    is_term.push_back(0);
    std::string curr_str = "";
    while (buff[i] != '\0') {
        if (opened_q) {
            switch (buff[i]) {
                case '\"':
                    opened_q = 0;
                    str_counter++;
                    flag *= -1;
                    subs.push_back(curr_str);
                    if (str_counter % 2 == 0)
                        is_term.push_back(0);
                    curr_str = "";
                    break;
                default:
                    curr_str = curr_str + buff[i];
                    break;
            }
        } else {
            switch (buff[i]) {
                case '\"':
                    opened_q = 1;
                    break;
                case '.':
                    if (flag != -1)
                        return -1;
                    is_term[str_counter / 2] = 1;
                    break;
                case ' ':
                case '\n':
                    break;
                default:
                    return -1;
                    break;
            }
        }
        i++;
    }
    if (str_counter % 2 == 1)
        return -1;
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
        case 0:
            break;
        default:
            print_error_message("file reading error occured");
            return 0;
            break;
    }
    std::vector <std::string> subs;
    std::vector <int> is_term;
    frerror = parse(buff, subs, is_term);
    free(buff);
    switch (frerror) {
        case -1:
            print_error_message("wrong syntax");
            return 0;
            break;
        case 0:
            break;
        default:
            print_error_message("unspecified error while parsing");
            break;
    }
    std::string inp;
    std::cin >> inp;
    bool halt = true;
    do {
        halt = true;
        for (int i = 0; i < (int)subs.size() / 2; i++) {
            int it = (int)inp.find(subs[i * 2]);
            if (it < (int)inp.size() && it >= 0) {
                halt = (bool)is_term[i];
                inp.replace(it, (int)subs[i * 2].size(), subs[i * 2 + 1]);
                break;
            }
        }
    } while (!halt);
    std::cout << inp << "\n";
    return 0;
}
