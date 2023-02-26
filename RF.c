#include "RF.h"
#include "register.h"
#include "library.h"
#include "instruction.h"

void RF(reg_set *regs) {
    unsigned int inst32 = regs->src->rfs->inst32;
    ex_stage *tgt = regs->tgt->exs;
    tgt->op = identify_opecode(inst32);
    tgt->f5 = identify_funct5(inst32);
    tgt->f3 = identify_funct3(inst32);
    tgt->dest = cut(inst32, 23, 16);
    unsigned int src1 = cut(inst32, 15, 8);
    unsigned int src2 = cut(inst32, 7, 0);
    tgt->src1 = src1;
    tgt->src2 = src2;
    tgt->read1 = regs->reg[src1];
    tgt->read2 = regs->reg[src2];
    tgt->imm8 = cut(inst32, 7, 0);
    tgt->imm10 = cut(inst32, 25, 16);
    tgt->imm26 = cut(inst32, 25, 0);
    tgt->pc = regs->src->rfs->pc;
}