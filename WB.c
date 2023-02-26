#include "WB.h"
#include "register.h"

void WB(reg_set* regs) {
    wb_stage *src = regs->src->wbs;
    if(src->WE) {
        regs->reg[src->dest] = src->data;
    }
}