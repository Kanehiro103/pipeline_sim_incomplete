#ifndef _GRAD_LIST_H_
#define _GRAD_LIST_H_

#define GRAD_LIST_SIZE 1024

// finvの計算で使用
unsigned long finv_list[GRAD_LIST_SIZE];

unsigned int finv_grad[GRAD_LIST_SIZE];
unsigned int finv_intercept[GRAD_LIST_SIZE];

// fsqrtの計算で使用
unsigned long fsqrt_list[GRAD_LIST_SIZE];
unsigned int fsqrt_grad[GRAD_LIST_SIZE];
unsigned int fsqrt_intercept[GRAD_LIST_SIZE];

#endif