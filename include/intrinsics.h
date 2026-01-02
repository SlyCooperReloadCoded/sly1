/**
 * @file intrinsics.h
 *
 * @brief Hardware intrinsics and inline assembly macros for MIPS/PS2 EE.
 */
#ifndef INTRINSICS_H
#define INTRINSICS_H

/**
 * @brief Hardware square root using MIPS FPU sqrt.s instruction.
 *
 * @details Inline assembly to invoke the standard MIPS II FPU sqrt.s
 * instruction. Available on R5900 (PS2 EE) and most MIPS processors with an
 * FPU.
 *
 * @param value Expression to compute square root of
 * @return Square root result as a float
 */
#define SQRTF(value)                                                           \
    ({                                                                         \
        float __result;                                                        \
        __asm__ volatile("sqrt.s %0, %1"                                       \
                         : "=&f"(__result)                                     \
                         : "f"(value)                                          \
                         : "memory");                                          \
        __result;                                                              \
    })
