#include "tables.h"

AsmReg REGISTERS[] = {
	{ "AX", 0x00, REG_GEN, REG_WORD },	{ "CX", 0x01, REG_GEN, REG_WORD },

	{ "DX", 0x02, REG_GEN, REG_WORD },	{ "BX", 0x03, REG_GEN, REG_WORD },

	{ "SP", 0x04, REG_GEN, REG_WORD },	{ "BP", 0x05, REG_GEN, REG_WORD },

	{ "SI", 0x06, REG_GEN, REG_WORD },	{ "DI", 0x07, REG_GEN, REG_WORD },

	{ "ES", 0x00, REG_SEG, REG_WORD },	{ "CS", 0x01, REG_SEG, REG_WORD },

	{ "SS", 0x02, REG_SEG, REG_WORD },	{ "DS", 0x03, REG_SEG, REG_WORD },
	{ "FS", 0x04, REG_SEG, REG_WORD },	{ "GS", 0x05, REG_SEG, REG_WORD },

	{ "EAX", 0x00, REG_GEN, REG_DWOR }, { "ECX", 0x01, REG_GEN, REG_DWOR },
	{ "EDX", 0x02, REG_GEN, REG_DWOR }, { "EBX", 0x03, REG_GEN, REG_DWOR },

	{ "ESP", 0x04, REG_GEN, REG_DWOR }, { "EBP", 0x05, REG_GEN, REG_DWOR },
	{ "ESI", 0x06, REG_GEN, REG_DWOR }, { "EDI", 0x07, REG_GEN, REG_DWOR },

};
uint8_t NUM_REGS = sizeof( REGISTERS ) / sizeof( *REGISTERS );

const AsmMnem MNEMONICS[] = {
	{ "ADD", 0, 6 },
};
const uint8_t NUM_MNEMONICS = sizeof( MNEMONICS ) / sizeof( *MNEMONICS );

AsmOpc OPCODES[] = {
	{ { 0x00 }, 0, 0x00, { { ASM_ADDR_E, ASM_OPER_B }, { ASM_ADDR_G, ASM_OPER_B } } },
	{ { 0x01 }, 0, 0x00, { { ASM_ADDR_E, ASM_OPER_VQP }, { ASM_ADDR_G, ASM_OPER_VQP } } },
	{ { 0x02 }, 0, 0x00, { { ASM_ADDR_G, ASM_OPER_B }, { ASM_ADDR_E, ASM_OPER_B } } },
	{ { 0x03 }, 0, 0x00, { { ASM_ADDR_G, ASM_OPER_VQP }, { ASM_ADDR_E, ASM_OPER_VQP } } },
};
uint16_t NUM_OPCODES;
