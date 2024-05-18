#include "./include/fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file_fs(const char* path_name) {
    FILE* fp = fopen(path_name, "r+");
    
    if (!fp) {
        fprintf(stderr, "(%s) is not a valid file in this current directory.", path_name);
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = calloc(length, length);
    fread(buffer, 1, length, fp);
    return buffer;
}

size_t len_file_fs(const char* path_name) {
    FILE* fp = fopen(path_name, "r+");
    
    if (!fp) {
        fprintf(stderr, "Cannot read length of file (%s), as it is not a valid file in this current directory.", path_name);
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    size_t length = ftell(fp);
    return length;
}
void write_file_fs(const char* path_name, char* contents) {
    FILE* fp = fopen(path_name, "wb");
    if (!fp) {
        fprintf(stderr, "Cannot write to (%s) as it is not a valid file in this current directory.", path_name);
        exit(1);
    }
    fwrite(contents, sizeof(char), strlen(contents), fp);
}

void shell_cmd_fs(const char* cmd) {
    system(cmd);
}