#include "memory.h"
#include "register.h"

unsigned int mem_fetch(reg_set* regs, unsigned int addr, unsigned int stage) {
    /*
    if(regs->clk % 10 == 0) {
        if(stage) {
            regs->hzd->stl_if += 5;
        } else {
            regs->hzd->stl_ex += 5;
        }
    }
    */
    return regs->mem[addr];
}