#pragma once

#include <stdint.h>

enum {
	PROSE_JMP_REL,
	PROSE_PSH_IMM,
	PROSE_POP_VAL,
};

typedef struct {
	uint8_t* data;
	uint64_t size;
} prose_rom_t;

typedef struct {
	uint64_t* stack;
	uint64_t stack_size;
	uint64_t sp;
	uint64_t bp;
	uint64_t pc;
	prose_rom_t* rom;
} prose_vm_t;

prose_vm_t init_prose_vm( uint64_t stack_size );

void load_rom( prose_vm_t* vm, prose_rom_t* rom );
