#include "opcodes.h"

x64_mnem_t mnems[] = {
	{ "add", 0, 6 },
	{ "movq", 0, 0 },
	{ "ret", 0, 0 },
};
uint16_t num_mnems = sizeof( mnems ) / sizeof( mnems[ 0 ] );

x64_opcode_t opcodes[] = {
	{},
};
uint16_t num_opcodes = sizeof( opcodes ) / sizeof( opcodes[ 0 ] );

x64_reg_t regs[] = {
	{ "rax", X64_REG_Q, 0x00 },
	{ "rcx", X64_REG_Q, 0x01 },
	{ "rdx", X64_REG_Q, 0x02 },
	{ "rbx", X64_REG_Q, 0x03 },

	{ "rsp", X64_REG_Q, 0x04 },
	{ "rbp", X64_REG_Q, 0x05 },
	{ "rsi", X64_REG_Q, 0x06 },
	{ "rdi", X64_REG_Q, 0x07 },

	{ "r8", X64_REG_Q | X64_R_REG, 0x00 },
	{ "r9", X64_REG_Q | X64_R_REG, 0x01 },
	{ "r10", X64_REG_Q | X64_R_REG, 0x02 },
	{ "r11", X64_REG_Q | X64_R_REG, 0x03 },

	{ "r12", X64_REG_Q | X64_R_REG, 0x04 },
	{ "r13", X64_REG_Q | X64_R_REG, 0x05 },
	{ "r14", X64_REG_Q | X64_R_REG, 0x06 },
	{ "r15", X64_REG_Q | X64_R_REG, 0x07 },

};
uint8_t num_regs = sizeof( regs ) / sizeof( regs[ 0 ] );
