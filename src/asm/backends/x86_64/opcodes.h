#pragma once

#include <stdint.h>

#define X64_MNEM_MAX 32
#define X64_ARG_MAX 3

typedef enum
{
	X64_REG_B,
	X64_REG_W,
	X64_REG_D,
	X64_REG_Q,
	X64_R_REG = 1 << 7,	 // expanded r-prefix registers (r8-r15)
} x64_reg_type_t;

typedef struct
{
	const char* name;
	x64_reg_type_t type;
	uint8_t code;
} x64_reg_t;

typedef struct
{
	const char* name;
	uint16_t idx;  // index in the opcode table
	uint8_t num;   // number of variants
} x64_mnem_t;

typedef enum
{
	X64_N_ARG,
	X64_ARG_A,
} x64_arg_profile_t;

typedef struct
{
	uint8_t opcode;
	x64_arg_profile_t args[ X64_ARG_MAX ];
} x64_opcode_t;

extern x64_mnem_t mnems[];
extern uint16_t num_mnems;

extern x64_opcode_t opcodes[];
extern uint16_t num_opcodes;

extern x64_reg_t regs[];
extern uint8_t num_regs;
