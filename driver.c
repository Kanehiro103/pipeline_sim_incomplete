#include "driver.h"
#include "register.h"
#include "WB.h"
#include "EX.h"
#include "RF.h"
#include "IF.h"

void copy_wbs(wb_stage *wbs1, wb_stage *wbs2) {
    wbs1->WE = wbs2->WE;
    wbs1->dest = wbs2->dest;
    wbs1->data = wbs2->data;
}

void copy_exs(ex_stage *exs1, ex_stage *exs2) {
    exs1->op = exs2->op;
    exs1->f5 = exs2->f5;
    exs1->f3 = exs2->f3;
    exs1->dest = exs2->dest;
    exs1->src1 = exs2->src1;
    exs1->src2 = exs2->src2;
    exs1->read1 = exs2->read1;
    exs1->read2 = exs2->read2;
    exs1->imm8 = exs2->imm8;
    exs1->imm10 = exs2->imm10;
    exs1->imm26 = exs2->imm26;
    exs1->pc = exs2->pc;
}

void copy_rfs(rf_stage *rfs1, rf_stage *rfs2) {
    rfs1->inst32 = rfs2->inst32;
    rfs1->pc = rfs2->pc;
}

void copy(unit *un1, unit *un2) {
    copy_wbs(un1->wbs, un2->wbs);
    copy_exs(un1->exs, un2->exs);
    copy_rfs(un1->rfs, un2->rfs);
    un1->pc = un2->pc;
}

void drive(reg_set *regs, int oppm, FILE *fppm, int oinput, FILE *finput) {
    branch *branch = regs->branch;
    hazard *hzd = regs->hzd;
    unit *src = regs->src;
    unit *tgt = regs->tgt;

    regs->clk++;

    if(hzd->stl_ex) {
        flash_wbs(src->wbs);
        WB(regs);
    } else if(hzd->stl_if) {

        copy_wbs(src->wbs, tgt->wbs);
        copy_exs(src->exs, tgt->exs);
        flash_rfs(src->rfs);

        WB(regs);
        EX(regs, oppm, fppm, oinput, finput);
        RF(regs);

        if(branch->j_flag) {
            hzd->stl_if = 0;
            flash_exs(tgt->exs);
            flash_rfs(tgt->rfs);
            tgt->pc = branch->j_pc;
        } else {
            tgt->pc = src->pc + 1;
        }
        flash_branch(branch);
    } else {
        copy(src, tgt);

        WB(regs);
        EX(regs, oppm, fppm, oinput, finput);
        RF(regs);
        IF(regs);

        if(branch->j_flag) {
            hzd->stl_if = 0;
            flash_exs(tgt->exs);
            flash_rfs(tgt->rfs);
            tgt->pc = branch->j_pc;
        } else {
            tgt->pc = src->pc + 1;
        }
        flash_branch(branch);
    }
    if(hzd->stl_ex) {
        hzd->stl_ex--;
    }
    if(hzd->stl_if) {
        hzd->stl_if--;
    }
}