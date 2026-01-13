#include "opcodes.h"

x64_mnem_t mnems[] = {
	{ "movq", 0, 0 },
	{ "ret", 0, 0 },
};
uint16_t num_mnems = sizeof( mnems ) / sizeof( mnems[ 0 ] );

x64_opcode_t opcodes[] = {
	{},
};
uint16_t num_opcodes = sizeof( opcodes ) / sizeof( opcodes[ 0 ] );

x64_reg_t regs[] = {
	{ "rax", X64_REG_Q | X64_R_REG, 0x00 },
	{ "rcx", X64_REG_Q | X64_R_REG, 0x01 },
	{ "rdx", X64_REG_Q | X64_R_REG, 0x02 },
	{ "rbx", X64_REG_Q | X64_R_REG, 0x03 },

};
uint8_t num_regs = sizeof( regs ) / sizeof( regs[ 0 ] );
