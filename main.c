#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "register.h"
#include "library.h"
#include "read.h"
#include "driver.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc <= 1) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    FILE *finput = NULL;
    int oinput = 0;
    if(argc == 3) {
        char* input = "./input/";
        char input_file[128];
        sprintf(input_file, "%s%s", input, argv[2]);
        //fps.fpi = fopen(input_file, "r");
        finput = fopen(input_file, "rb");
        if(finput == NULL) {
            printf("file not found");
            exit(1);
        } else {
            oinput = 1;
        }
    }

    reg_set *regs = (reg_set*)malloc(sizeof(reg_set));
    init_regs(regs);

    regs->mem[0xfffffff8] = 1024;
    regs->mem[0xfffffff2] = 1024;

    char *samples = "./samples/";
    char *dat = ".dat";
    char read_file[128];
    sprintf(read_file, "%s%s%s", samples, argv[1], dat);

    if(read_(regs, read_file)) {
        printf("file not found\n");
        exit(1);
    }

    int flag = 0;
    char s[16];
    while(1) {
        printf("ppm? y/n : ");
        scanf("%s", s);
        if(strcmp(s, "y") == 0) {
            flag = 1;
            break;
        } else if(strcmp(s, "n") == 0) {
            break;
        } else {
            continue;
        }
    }
    
    FILE  *fppm = NULL;
    int oppm = 0;

    if(flag) {
        char *uartfiles = "./ppm/uart_";
        char uart_file[128];
        char *ppm = ".ppm";
        sprintf(uart_file, "%s%s%s", uartfiles, argv[1], ppm);
        fppm = fopen(uart_file, "w");

        if(fppm == NULL) {
            printf("failed to open ppm file.\n");
            exit(1);
        } else {
            oppm = 1;
        }
    }


    while(!regs->hzd->f_flag) {
        drive(regs, oppm, fppm, oinput, finput);
        //printf("r1:%u\n", regs->reg[1]);
        //printf("pc:%u\n", regs->src->pc);
        //printf("r251 %d\n", regs->reg[251]);
        //usleep(100000);
    }
    

    printf("r0 =  %u\n", regs->reg[0]);
    printf("clk  = %lu\n", regs->clk);

    free_regs(regs);
    if(oppm) {
        fclose(fppm);
    }
    if(oinput) {
        fclose(finput);
    }
    return 0;
}