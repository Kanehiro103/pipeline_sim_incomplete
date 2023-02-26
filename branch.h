#ifndef _BRANCH_H_
#define _BRANCH_H_

#include "register.h"

void beq_num(unsigned int, unsigned int, unsigned int, unsigned int, hazard*, branch*);
void blt_num(unsigned int, unsigned int, unsigned int, unsigned int, hazard*, branch*);
void ble_num(unsigned int, unsigned int, unsigned int, unsigned int, hazard*, branch*);
void j_num(unsigned int, unsigned int, hazard*, branch*);
void jr_num(unsigned int, unsigned int, hazard*, branch*);

#endif