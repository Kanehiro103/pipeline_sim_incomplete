#include "instruction.h"
#include "library.h"

// オペコードの識別
enum opecode identify_opecode(unsigned int inst32) {
    switch(cut(inst32, 31, 29)) {
        case 0: return OOO_op;
        case 1: return OOI_op;
        case 2: return OIO_op;
        case 4: return IOO_op;
        case 5: return IOI_op;
        case 7: return III_op;
        case 6: return IIO_op;
        default: return Undefined_opecode;
    }
}

// funct(5桁)の識別
enum funct5 identify_funct5(unsigned int inst32) {
    switch(cut(inst32, 28, 24)) {
        case 1: return OOOOI;
        case 2: return OOOIO;
        case 4: return OOIOO;
        case 8: return OIOOO;
        case 16: return IOOOO;
        case 17: return IOOOI;
        case 18: return IOOIO;
        case 20: return IOIOO;
        case 24: return IIOOO;
        default: return Undefined_funct5;
    }
}

// funct(3桁)の識別
enum funct3 identify_funct3(unsigned int inst32) {
    switch(cut(inst32, 28, 26)) {
        case 1: return OOI;
        case 2: return OIO;
        case 4: return IOO;
        case 0: return OOO;
        default: return Undefined_funct3;
    }
}

// ニーモニックの識別
enum nemonic identify_nemonic(enum opecode opecode, enum funct5 funct5, enum funct3 funct3) {
    switch(opecode) {
        case OOO_op:    switch(funct5) {
                            case OOOOI: return ADD;
                            case OOOIO: return SUB;
                            case OIOOI: return SLL;
                            case OIOIO: return SRL;
                            case OIIOO: return SRA;
                            case IOOOI: return FISPOS;
                            case IOOIO: return FISNEG;
                            case IOIOO: return FNEG;
                            default: return UNDEFINED;
                        }
        case OOI_op:    switch(funct5) {
                            case OOOOI: return ADDI;
                            case OOOIO: return SUBI;
                            case OOIOO: return SLLI;
                            case OIOOO: return SRLI;
                            case IOOOO: return SRAI;
                            default: return UNDEFINED;
                        }
                        return UNDEFINED;
        case OIO_op:    switch(funct5) {
                            case OOOOI: return FADD;
                            case OOOIO: return FSUB;
                            case OOIOO: return FMUL;
                            case OIOOO: return FDIV;
                            case IOOOI: return FLESS;
                            case IOOIO: return FTOI;
                            case IOIOO: return ITOF;
                            case IIOOO: return FSQRT;
                            default: return UNDEFINED;
                        }
        case IOO_op:    switch(funct3) {
                            case OOI: return BEQ;
                            case OIO: return BLT;
                            case IOO: return BLE;
                            default: return UNDEFINED;
                        }
        case IOI_op:    switch(funct3) {
                            case OOO: return J;
                            case OOI: return JR;
                            default: return UNDEFINED;
                        }
        case III_op:    switch(funct3) {
                            case OOO: return LW;
                            default: return UNDEFINED;
                        }
        case IIO_op:    switch(funct3) {
                            case OOO: return SW;
                            default: return UNDEFINED;
                        }
        default:  return UNDEFINED;
    }
}