#include "branch.h"
#include "register.h"
#include "library.h"

void beq_num(unsigned int read1, unsigned int read2, unsigned int pc, unsigned int imm10, hazard* hzd, branch* branch) {
    if(read1 == read2) {
        branch->j_flag = 1;
        branch->j_pc = pc + to_signed(imm10, 10);
        if(pc == branch->j_pc) {
            hzd->f_flag = 1;
        } else {
            hzd->f_flag = 0;
        }
    }
}

void blt_num(unsigned int read1, unsigned int read2, unsigned int pc, unsigned int imm10, hazard* hzd, branch* branch) {
    if(read1 < read2) {
        branch->j_flag = 1;
        branch->j_pc = pc + to_signed(imm10, 10);
        if(pc == branch->j_pc) {
            hzd->f_flag = 1;
        } else {
            hzd->f_flag = 0;
        }
    }
}

void ble_num(unsigned int read1, unsigned int read2, unsigned int pc, unsigned int imm10, hazard* hzd, branch* branch) {
    if(read1 <= read2) {
        branch->j_flag = 1;
        branch->j_pc = pc + to_signed(imm10, 10);
        if(pc == branch->j_pc) {
            hzd->f_flag = 1;
        } else {
            hzd->f_flag = 0;
        }
    }
}

void j_num(unsigned int pc, unsigned int imm26, hazard* hzd, branch* branch) {
    branch->j_flag = 1;
    branch->j_pc = pc + to_signed(imm26, 26);
    if(pc == branch->j_pc) {
            hzd->f_flag = 1;
        } else {
            hzd->f_flag = 0;
        }
}

void jr_num(unsigned int pc, unsigned int read2, hazard* hzd, branch* branch) {
    branch->j_flag = 1;
    branch->j_pc = read2;
    if(pc == branch->j_pc) {
            hzd->f_flag = 1;
        } else {
            hzd->f_flag = 0;
        }
}