#include "IF.h"
#include "register.h"
#include "memory.h"

void IF(reg_set *regs) {
    rf_stage *tgt = regs->tgt->rfs;
    unsigned int pc = regs->src->pc;
    //tgt->inst32 = regs->mem[pc];
    tgt->inst32 = mem_fetch(regs, pc, 1);
    tgt->pc = pc;
}