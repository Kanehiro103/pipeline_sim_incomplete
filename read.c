#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "register.h"

//16進表記の命令が書き込まれたファイルを受け取り、メモリに書き込む
//命令は改行(\r, \n)で区切られる
int read_(reg_set* regs, char* fname) {
    FILE* fp;
    char str[BUFFER_SIZE];
    char* endptr;
    int i = 0;

    fp = fopen(fname, "r");
    if(fp == NULL) {
        return 1;
    }

    while(fgets(str, BUFFER_SIZE, fp) != NULL) {
        unsigned int num = (unsigned int)strtol(str, &endptr, 16);
        if(*endptr == '\r' || *endptr == '\n') {
            regs->mem[i] = num;
            i++;
        }
    }

    fclose(fp);

    return 0;
}