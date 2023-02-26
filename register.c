#include "register.h"
#include "instruction.h"
#include <stdlib.h>
#include <stdio.h>

void flash_wbs(wb_stage *wbs) {
    wbs->WE = 0;
    wbs->dest = 0;
    wbs->data = 0;
}

void flash_exs(ex_stage *exs)  {
    exs->op = Undefined_opecode;
    exs->f5 = Undefined_funct5;
    exs->f3 = Undefined_funct3;
    exs->dest = 0;
    exs->src1 = 0;
    exs->src2 = 0;
    exs->read1 = 0;
    exs->read2 = 0;
    exs->imm8 = 0;
    exs->imm10 = 0;
    exs->imm26 = 0;
    exs->pc = 0;
}

void flash_rfs(rf_stage *rfs) {
    rfs->inst32 = 0;
    rfs->pc = 0;
}

void flash_branch(branch *branch) {
    branch->j_flag = 0;
    branch->j_pc = 0;
}

void flash_hzd(hazard *hzd) {
    hzd->f_flag = 0;
    hzd->stl_ex = 0;
    hzd->stl_if = 0;
}

void init_unit(unit *un)  {
    un->wbs = (wb_stage*)malloc(sizeof(wb_stage));
    flash_wbs(un->wbs);
    un->exs = (ex_stage*)malloc(sizeof(ex_stage));
    flash_exs(un->exs);
    un->rfs = (rf_stage*)malloc(sizeof(rf_stage));
    flash_rfs(un->rfs);
    un->pc = 0;
}

void init_regs(reg_set *regs) {
    regs->clk = 0;
    regs->src = (unit*)malloc(sizeof(unit));
    init_unit(regs->src);
    regs->tgt = (unit*)malloc(sizeof(unit));
    init_unit(regs->tgt);
    regs->branch = (branch*)malloc(sizeof(branch));
    flash_branch(regs->branch);
    regs->hzd = (hazard*)malloc(sizeof(hazard));
    flash_hzd(regs->hzd);
    regs->reg = (unsigned int*)calloc(REG_SIZE, sizeof(unsigned int));
    regs->mem = (unsigned int*)calloc(MEM_SIZE, sizeof(unsigned int));
}

void free_unit(unit *un) {
    free(un->wbs);
    free(un->exs);
    free(un->rfs);
    free(un);
}

void free_regs(reg_set *regs) {
    free_unit(regs->src);
    free_unit(regs->tgt);
    free(regs->branch);
    free(regs->hzd);
    free(regs);
}