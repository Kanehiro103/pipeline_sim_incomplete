#ifndef _REGISTER_H_
#define _REGISTER_H_

#include "instruction.h"

#define REG_SIZE 256
#define MEM_SIZE 4294967296

typedef struct {
    unsigned int WE;
    unsigned int dest;
    unsigned int data;
} wb_stage;

typedef struct {
    enum opecode op;
    enum funct5 f5;
    enum funct3 f3;
    unsigned int dest;
    unsigned int src1;
    unsigned int src2;
    unsigned int read1;
    unsigned int read2;
    unsigned int imm8;
    unsigned int imm10;
    unsigned int imm26;
    unsigned int pc;
} ex_stage;

typedef struct {
    unsigned int inst32;
    unsigned int pc;
} rf_stage;

typedef struct {
    wb_stage *wbs;
    ex_stage *exs;
    rf_stage *rfs;
    unsigned int pc;
} unit;

typedef struct {
    unsigned int j_flag;
    unsigned int j_pc;
} branch;

typedef struct {
    unsigned int f_flag;
    unsigned int stl_ex;
    unsigned int stl_if;
} hazard;

typedef struct {
    unsigned long clk;
    unit *src;
    unit *tgt;
    branch *branch;
    hazard *hzd;
    unsigned int *reg;
    unsigned int *mem;
} reg_set;

void flash_wbs(wb_stage*);
void flash_exs(ex_stage*);
void flash_rfs(rf_stage*);
void flash_branch(branch*);

void init_regs(reg_set*);
void free_regs(reg_set*);

#endif