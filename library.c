#include "library.h"
#include <math.h>

#define CUT 31
#define CUT_UL 63

// ここから
// 2^i
unsigned int pow2(unsigned int i) { // unsigned int
    unsigned int ans = 1;
    return ans << i;
}
unsigned long pow2_ul(unsigned int i) { // unsigned long
    unsigned long ans = 1;
    return ans << i;
}
// ここまで

unsigned int cut(unsigned int num, unsigned int a, unsigned int b) {
    return (num << (CUT - a)) >> (CUT - a + b);
}

unsigned long cut_ul(unsigned long num, unsigned int a, unsigned int b) {
    return (num << (CUT_UL - a)) >> (CUT_UL - a + b);
}

float to_float(unsigned int x) {
    union fu u;
    u.u = x;
    return u.f;
}

unsigned int to_fpn(float x) {
    union fu f;
    f.f = x;
    return f.u;
}

// ここから
int to_signed(unsigned int num, int i) {
    unsigned int s = cut(num, i - 1, i - 1);
    unsigned int m = cut(num, i - 2, 0);
    if(s == 0) {
        return (int)m;
    } else {
        return ((int)pow2(i - 1) - (int)m) * (-1);
    }
}

unsigned int fpn(unsigned int s, unsigned int e, unsigned int m) {
    return (s << 31) + (e << 23) + m;
}