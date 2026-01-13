#pragma once

#include <stdint.h>

enum : uint8_t
{  // instruction set!
	PROSE_HLT_CPU,
	PROSE_JMP_REL,
	PROSE_PSH_IMM,
	PROSE_POP_OFF,
	PROSE_ADD_TOP,
	PROSE_SUB_TOP,
	PROSE_MUL_TOP,
	PROSE_DIV_TOP,
	PROSE_SWP_STK,
	PROSE_JMP_IFZ,
	PROSE_JMP_IFP,
	PROSE_JMP_IFN,
	PROSE_IAD_TOP,
	PROSE_ISB_TOP,
	PROSE_IML_TOP,
	PROSE_IDV_TOP,

};

typedef enum : uint8_t
{
	PROSE_COND_NONE,
	PROSE_COND_HALT,
	PROSE_COND_EXCP,
} prose_escape_condition_t;

typedef struct
{
	uint64_t size;
	uint64_t entry;
	uint8_t data[];
} prose_rom_t;

typedef struct
{
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
