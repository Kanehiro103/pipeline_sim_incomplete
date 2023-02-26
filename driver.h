#ifndef _DRIVER_H_
#define _DRIVER_H_

#include "register.h"
#include <stdio.h>

void drive(reg_set *regs, int, FILE*, int, FILE*);

#endif