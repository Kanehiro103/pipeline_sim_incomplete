#include "EX.h"
#include "register.h"
#include "alu.h"
#include "fpu.h"
#include "branch.h"
#include "instruction.h"
#include "memory.h"

#define READ_SIZE 1

unsigned int uart_read_b(FILE* fp) {
    if(fp == NULL) {
        return 0;
    } else {
        unsigned int a = 0;
        if(fread(&a, sizeof(unsigned int), READ_SIZE, fp) < READ_SIZE) {
            return 0;
        } else {
            return a;
        }
    }
}

void EX(reg_set *regs, int oppm, FILE *fppm, int oinput, FILE *finput) {
    ex_stage *src = regs->src->exs;
    wb_stage *tgt = regs->tgt->wbs;
    branch *branch = regs->branch;
    hazard *hzd = regs->hzd;
    wb_stage *forward = regs->src->wbs;

    unsigned int read1, read2;
    if(forward->WE && forward->dest == src->src1) {
        read1 = forward->data;
    } else {
        read1 = src->read1;
    }
    if(forward->WE && forward->dest == src->src2) {
        read2 = forward->data;
    } else {
        read2 = src->read2;
    }

    switch(identify_nemonic(src->op, src->f5, src->f3)) {
        case ADD:   tgt->WE = 1;
                    tgt->data = add_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case SUB:   tgt->WE = 1;
                    tgt->data = sub_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case SLL:   tgt->WE = 1;
                    tgt->data = sll_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case SRL:   tgt->WE = 1;
                    tgt->data = srl_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case SRA:   tgt->WE = 1;
                    tgt->data = sra_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case FISPOS:    tgt->WE = 1;
                        tgt->data = fispos_num(read2);
                        tgt->dest = src->dest;
                        break;
        case FISNEG:    tgt->WE = 1;
                        tgt->data = fisneg_num(read2);
                        tgt->dest = src->dest;
                        break;
        case FNEG:      tgt->WE = 1;
                        tgt->data = fneg_num(read2);
                        tgt->dest = src->dest;
                        break;
        case ADDI:  tgt->WE = 1;
                    tgt->data = addi_num(read1, src->imm8);
                    tgt->dest = src->dest;
                    break;
        case SUBI:  tgt->WE = 1;
                    tgt->data = subi_num(read1, src->imm8);
                    tgt->dest = src->dest;
                    break;
        case SLLI:  tgt->WE = 1;
                    tgt->data = slli_num(read1, src->imm8);
                    tgt->dest = src->dest;
                    break;
        case SRLI:  tgt->WE = 1;
                    tgt->data = srli_num(read1, src->imm8);
                    tgt->dest = src->dest;
                    break;
        case SRAI:  tgt->WE = 1;
                    tgt->data = srai_num(read1, src->imm8);
                    tgt->dest = src->dest;
                    break;
        case FADD:  tgt->WE = 1;
                    tgt->data = fadd_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case FSUB:  tgt->WE = 1;
                    tgt->data = fsub_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case FMUL:  tgt->WE = 1;
                    tgt->data = fmul_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case FDIV:  tgt->WE = 1;
                    tgt->data = fdiv_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case FLESS: tgt->WE = 1;
                    tgt->data = fless_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case FTOI:  tgt->WE = 1;
                    tgt->data = ftoi_num(read2);
                    tgt->dest = src->dest;
                    break;
        case ITOF:  tgt->WE = 1;
                    tgt->data = itof_num(read2);
                    tgt->dest = src->dest;
                    break;
        case FSQRT: tgt->WE = 1;
                    tgt->data = fsqrt_num(read2);
                    tgt->dest = src->dest;
                    break;
        case BEQ:   flash_wbs(tgt);
                    beq_num(read1, read2, src->pc, src->imm10, hzd, branch);
                    break;
        case BLT:   flash_wbs(tgt);
                    blt_num(read1, read2, src->pc, src->imm10, hzd, branch);
                    break;
        case BLE:   flash_wbs(tgt);
                    ble_num(read1, read2, src->pc, src->imm10, hzd, branch);
                    break;
        case J:     flash_wbs(tgt);
                    j_num(src->pc, src->imm26, hzd, branch);
                    break;
        case JR:    flash_wbs(tgt);
                    jr_num(src->pc, read2, hzd, branch);
                    break;
        case LW:    //printf("lw %u\n", src->pc);
                    //printf("r251: %d\n", regs->reg[251]);
                    //printf("read2 %d\n", read2);
                    tgt->WE = 1;
                    //tgt->data = regs->mem[read2];
                    unsigned int x1 = (read2 == -15) ? uart_read_b(finput) : mem_fetch(regs, read2, 0);
                    tgt->data = x1;
                    if (read2 == -15) { printf("%u %x\n", src->dest, x1); }
                    //tgt->data = mem_fetch(regs, read2, 0);
                    tgt->dest = src->dest;
                    break;
        case SW:    flash_wbs(tgt);
                    if(oppm  && read2 == -12) {
                        fprintf(fppm, "%c", read1);
                    }
                    regs->mem[read2] = read1;
                    break;
        default:    break;
    }
}