#pragma once

#define MNEMONIC_MAX 32

#include "tables.h"

typedef enum : uint8_t
{
	ASM_ARG_REG,
	ASM_ARG_IMM,
	ASM_ARG_MEM,
} AsmArgType;

typedef struct
{
	AsmReg *base;
	AsmReg *index;
	AsmReg *scale;
	int64_t displacement;
} AsmMemArg;

typedef struct
{
	AsmArgType type;
	union
	{
		AsmReg	 *reg;
		uint64_t  imm;
		AsmMemArg mem;
	};
} AsmArg;

typedef struct
{
	char	 mnemonic[ MNEMONIC_MAX ];
	uint64_t offset;
} AsmLabel;

typedef struct
{
	char   mnemonic[ MNEMONIC_MAX ];
	AsmArg args[ MAX_ARGS ];
} AsmIns;
