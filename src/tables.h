#pragma once

#include <stdint.h>

typedef enum : uint8_t
{
	REG_SEG,
	REG_GEN,
	REG_EXT,
} RegType;

typedef enum : uint8_t
{
	REG_WORD,
	REG_BYTE,
	REG_DWOR,
	REG_QWOR,
} RegSize;

typedef struct
{
	const char* name;
	uint8_t code;
	RegType type : 4;
	RegSize size : 4;
} AsmReg;

extern AsmReg REGISTERS[];
extern uint8_t NUM_REGS;

typedef struct
{
	const char* name;
	uint8_t codes[ 4 ];	// pf,
	uint8_t n_codes : 4;
	uint8_t extension;
} AsmOpc;

extern const char* MNEMS[];
extern const uint8_t NUM_MNEMS;

extern AsmOpc OPCODES[];
extern uint16_t NUM_OPCODES;
