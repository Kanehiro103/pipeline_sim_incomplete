#ifndef _ALU_H_
#define _ALU_H_

// 数値計算部分(整数)
unsigned int add_num(unsigned int, unsigned int);
unsigned int sub_num(unsigned int, unsigned int);
unsigned int sll_num(unsigned int, unsigned int);
unsigned int srl_num(unsigned int, unsigned int);
unsigned int sra_num(unsigned int, unsigned int);
unsigned int addi_num(unsigned int, unsigned int);
unsigned int subi_num(unsigned int, unsigned int);
unsigned int slli_num(unsigned int, unsigned int);
unsigned int srli_num(unsigned int, unsigned int);
unsigned int srai_num(unsigned int, unsigned int);
unsigned int fispos_num(unsigned int);
unsigned int fisneg_num(unsigned int);
unsigned int fneg_num(unsigned int);

#endif