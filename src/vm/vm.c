#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

prose_vm_t init_prose_vm( uint64_t stack_size )
{
	prose_vm_t vm;
	vm.bp = 0;
	vm.sp = stack_size;
	vm.stack = malloc( sizeof( uint64_t ) * stack_size );
	vm.rom = NULL;
	vm.escape_condition = PROSE_COND_NONE;
	return vm;
}

void delete_prose_vm( prose_vm_t* vm )
{
	free( vm->stack );
}

void prose_load_rom( prose_vm_t* vm, prose_rom_t* rom )
{
	vm->rom = rom;
	vm->pc = rom->entry;
}

void prose_psh( prose_vm_t* vm, uint64_t val )
{
	vm->stack[ vm->sp ] = val;
	vm->sp += 8;
}

void prose_jmp_rel( prose_vm_t* vm )
{
	vm->pc += vm->rom->data[ ++vm->pc ];
}
void prose_psh_imm( prose_vm_t* vm )
{
	prose_psh( vm, *(uint64_t*)&vm->rom->data[ ++vm->pc ] );
	vm->pc += 8;
}
void prose_pop( prose_vm_t* vm )
{
	// vm->stack[ vm->sp ];
	vm->sp -= 8;
}
void prose_add_top( prose_vm_t* vm )
{
	prose_psh( vm, vm->stack[ vm->sp ] + vm->stack[ vm->sp - 8 ] );
}
void prose_sub_top( prose_vm_t* vm )
{
	prose_psh( vm, vm->stack[ vm->sp ] - vm->stack[ vm->sp - 8 ] );
}
void prose_mul_top( prose_vm_t* vm )
{
	prose_psh( vm, vm->stack[ vm->sp ] * vm->stack[ vm->sp - 8 ] );
}
void prose_div_top( prose_vm_t* vm )
{
	prose_psh( vm, vm->stack[ vm->sp ] / vm->stack[ vm->sp - 8 ] );
}

void prose_execute( prose_vm_t* vm )
{
	while ( !vm->escape_condition ) {
		switch ( vm->rom->data[ vm->pc ] ) {
		case PROSE_JMP_REL:
			prose_jmp_rel( vm );
			break;
		case PROSE_PSH_IMM:
			prose_psh_imm( vm );
			break;
		case PROSE_POP_OFF:
			prose_pop( vm );
			break;
		case PROSE_ADD_TOP:
			prose_add_top( vm );
			break;
		case PROSE_SUB_TOP:
			prose_sub_top( vm );
			break;
		case PROSE_MUL_TOP:
			prose_mul_top( vm );
			break;
		case PROSE_DIV_TOP:
			prose_div_top( vm );
			break;
		case PROSE_HLT_CPU:
			vm->escape_condition = PROSE_COND_HALT;
		default:
			break;	// halt / exception
		}
	}
	switch ( vm->escape_condition ) {
	case PROSE_COND_HALT:
		printf( "Prose virtual machine halted.\n" );
		break;
	case PROSE_COND_EXCP:
		printf( "Prose virtual machine encountered exception and exited\n" );
		break;
	default:
		printf(
			"Prose virtual machine exited with unusual escape condition\n" );
		break;
	}
}
