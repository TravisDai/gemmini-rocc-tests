// See LICENSE for license details.

#ifndef SRC_MAIN_C_ROCC_H
#define SRC_MAIN_C_ROCC_H

#define STR1(x) #x
#define STR(x) STR1(x)
#define EXTRACT(a, size, offset) (((~(~0 << size) << offset) & a) >> offset)

#define CUSTOMX_OPCODE(x) CUSTOM_ ## x
#define CUSTOM_0 0b0001011
#define CUSTOM_1 0b0101011
#define CUSTOM_2 0b1011011
#define CUSTOM_3 0b1111011

#define CUSTOMX(X, rd, rs1, rs2, funct) \
  CUSTOMX_OPCODE(X)                   | \
  (rd                   << (7))       | \
  (0x7                  << (7+5))     | \
  (rs1                  << (7+5+3))   | \
  (rs2                  << (7+5+3+5)) | \
  (EXTRACT(funct, 7, 0) << (7+5+3+5+5))

// Standard macro that passes rd_, rs1_, and rs2_ via registers
#define ROCC_INSTRUCTION(XCUSTOM_, rd_, rs1_, rs2_, funct_)     \
  ROCC_INSTRUCTION_R_R_R(XCUSTOM_, rd_, rs1_, rs2_, funct_)

#define ROCC_INSTRUCTION_R_R_R(X, rd, rs1, rs2, funct)  \
  asm volatile (                                        \
       ".word "STR(CUSTOMX(X, 10, 11, 12, funct))"\n\t" \
       : "=r" (rd)                                      \
       : [_rs1] "r" (rs1), [_rs2] "r" (rs2));

// [TODO] fix these to align with the above approach
// Macro to pass rs2_ as an immediate
/*
#define ROCC_INSTRUCTION_R_R_I(XCUSTOM_, rd_, rs1_, rs2_, funct_) \
  asm volatile (XCUSTOM_" %[rd], %[rs1], %[rs2], %[funct]"        \
                : [rd] "=r" (rd_)                                 \
                : [rs1] "r" (rs1_), [rs2] "i" (rs2_), [funct] "i" (funct_))

// Macro to pass rs1_ and rs2_ as immediates
#define ROCC_INSTRUCTION_R_I_I(XCUSTOM_, rd_, rs1_, rs2_, funct_) \
  asm volatile (XCUSTOM_" %[rd], %[rs1], %[rs2], %[funct]"        \
                : [rd] "=r" (rd_)                                 \
                : [rs1] "i" (rs1_), [rs2] "i" (rs2_), [funct] "i" (funct_))
*/

#endif  // SRC_MAIN_C_ACCUMULATOR_H
