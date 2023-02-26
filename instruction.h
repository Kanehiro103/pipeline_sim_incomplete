#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

// オペコードとfunct
// O = 0, I = 1
enum opecode { OOO_op, OOI_op, OIO_op, IOO_op, IOI_op, III_op, IIO_op, Undefined_opecode }; // オペコード
enum funct5 { OOOOI, OOOIO, OOIOO, OIOOO, OIOOI, OIOIO, OIIOO, IOOOO, IOOOI, IOOIO, IOIOO, IIOOO, Undefined_funct5 };    // funct(5桁)
enum funct3 { OOI, OIO, IOO, OOO, Undefined_funct3 };   // funct(3桁)

// ニーモニック
enum nemonic  {
    ADD,
    SUB,
    SLL,
    SRL,
    SRA,
    ADDI,
    SUBI,
    SLLI,
    SRLI,
    SRAI,
    FISPOS,
    FISNEG,
    FNEG,
    FADD,
    FSUB,
    FMUL,
    FDIV,
    FLESS,
    FTOI,
    ITOF,
    FSQRT,
    BEQ,
    BLT,
    BLE,
    J,
    JR,
    LW,
    SW,
    UNDEFINED   // 不正なニーモニック
};

// 各種識別関数
enum opecode identify_opecode(unsigned int);    // オペコード
enum funct5 identify_funct5(unsigned int);  // funct(5桁)
enum funct3 identify_funct3(unsigned int);  // funct(3桁)
enum nemonic identify_nemonic(enum opecode, enum funct5, enum funct3);  // ニーモニック

#endif