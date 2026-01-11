#pragma once

#include <stdint.h>

enum {	// instruction set!
	PROSE_HLT_CPU = 0x00,
	PROSE_JMP_REL = 0x01,
	PROSE_PSH_IMM = 0x02,
	PROSE_POP_OFF = 0x03,
	PROSE_ADD_TOP = 0x04,
	PROSE_SUB_TOP = 0x05,
	PROSE_MUL_TOP = 0x06,
	PROSE_DIV_TOP = 0x07,
	PROSE_SWP_STK = 0x08,
};

typedef enum {
	PROSE_COND_NONE,
	PROSE_COND_HALT,
	PROSE_COND_EXCP,
} prose_escape_condition_t;

typedef struct {
	uint64_t size;
	uint64_t entry;
	uint8_t data[];
} prose_rom_t;

typedef struct {
	uint64_t* stack;
	uint64_t stack_size;
	uint64_t sp;
	uint64_t bp;
	uint64_t pc;
	uint64_t cc;
	prose_rom_t* rom;

	prose_escape_condition_t escape_condition;
} prose_vm_t;

prose_vm_t init_prose_vm( uint64_t stack_size );

void prose_load_rom( prose_vm_t* vm, prose_rom_t* rom );

void prose_execute( prose_vm_t* vm );

void delete_prose_vm( prose_vm_t* vm );
