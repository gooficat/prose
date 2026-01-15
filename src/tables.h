#pragma once

#include <stdint.h>

#define MAX_ARGS 4

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
	const char *name;
	uint8_t		code;
	RegType		type : 4;
	RegSize		size : 4;
} AsmReg;

extern AsmReg  REGISTERS[];
extern uint8_t NUM_REGS;

typedef enum : uint8_t
{
	ASM_ADDR_NONE = 0,
	ASM_ADDR_A,
	ASM_ADDR_B,
	ASM_ADDR_BB,
	ASM_ADDR_BD,
	ASM_ADDR_C,
	ASM_ADDR_CRN,
	ASM_ADDR_D,
	ASM_ADDR_DRN,
	ASM_ADDR_E,
	ASM_ADDR_ES,
	ASM_ADDR_EST,
	ASM_ADDR_F,
	ASM_ADDR_G,
	ASM_ADDR_H,
	ASM_ADDR_I,
	ASM_ADDR_J,
	ASM_ADDR_M,
	ASM_ADDR_N,
	ASM_ADDR_O,
	ASM_ADDR_P,
	ASM_ADDR_Q,
	ASM_ADDR_R,
	ASM_ADDR_S,
	ASM_ADDR_SC,
	ASM_ADDR_T,
	ASM_ADDR_U,
	ASM_ADDR_V,
	ASM_ADDR_W,
	ASM_ADDR_X,
	ASM_ADDR_Y,
	ASM_ADDR_Z
} AsmAddrMode;

typedef enum : uint8_t
{
	ASM_OPER_NONE = 0,
	ASM_OPER_A,
	ASM_OPER_B,
	ASM_OPER_BCD,
	ASM_OPER_BS,
	ASM_OPER_BSQ,
	ASM_OPER_BSS,
	ASM_OPER_C,
	ASM_OPER_D,
	ASM_OPER_DI,
	ASM_OPER_DQ,
	ASM_OPER_DQP,
	ASM_OPER_DR,
	ASM_OPER_DS,
	ASM_OPER_E,
	ASM_OPER_ER,
	ASM_OPER_P,
	ASM_OPER_PI,
	ASM_OPER_PD,
	ASM_OPER_PS,
	ASM_OPER_PSQ,
	ASM_OPER_PT,
	ASM_OPER_PTP,
	ASM_OPER_Q,
	ASM_OPER_QI,
	ASM_OPER_QP,
	ASM_OPER_S,
	ASM_OPER_SD,
	ASM_OPER_SI,
	ASM_OPER_SR,
	ASM_OPER_SS,
	ASM_OPER_ST,
	ASM_OPER_STX,
	ASM_OPER_T,
	ASM_OPER_V,
	ASM_OPER_VDS,
	ASM_OPER_VQ,
	ASM_OPER_VQP,
	ASM_OPER_VS,
	ASM_OPER_W,
	ASM_OPER_WI,
} AsmTypeMode;

typedef struct
{
	AsmAddrMode mode;
	AsmTypeMode type;
} AsmParam;

typedef struct
{
	uint8_t	 codes[ 4 ];  // rex, pf, 0f, opc
	uint8_t	 n_codes : 4;
	uint8_t	 extension;
	AsmParam params[ MAX_ARGS ];
} AsmOpc;

typedef struct
{
	const char *name;
	uint16_t	index;
	uint8_t		vnum;
} AsmMnem;

extern const AsmMnem MNEMONICS[];
extern const uint8_t NUM_MNEMONICS;

extern AsmOpc	OPCODES[];
extern uint16_t NUM_OPCODES;
