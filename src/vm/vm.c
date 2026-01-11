#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

prose_vm_t init_prose_vm( uint64_t stack_size )
{
	prose_vm_t vm;
	vm.bp = 0;
	vm.sp = stack_size;
	vm.stack = calloc( sizeof( uint64_t ) * stack_size, sizeof( uint64_t ) );
	vm.stack_size = stack_size;
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
	if ( vm->sp <= 0 ) {
		vm->escape_condition = PROSE_COND_EXCP;
	}
	--vm->sp;
	vm->stack[ vm->sp ] = val;
}

void prose_jmp_rel( prose_vm_t* vm )
{
	vm->pc += (int8_t)vm->rom->data[ ++vm->pc ];
}
void prose_psh_imm( prose_vm_t* vm )
{
	prose_psh( vm, *(uint64_t*)&vm->rom->data[ ++vm->pc ] );
	vm->pc += 8;
}
void prose_pop( prose_vm_t* vm )
{
	// vm->stack[ vm->sp ];
	++vm->sp;
}
void prose_add_top( prose_vm_t* vm )
{
	++vm->pc;
	prose_psh( vm, vm->stack[ vm->sp ] + vm->stack[ vm->sp + 1 ] );
}
void prose_sub_top( prose_vm_t* vm )
{
	++vm->pc;
	prose_psh( vm, vm->stack[ vm->sp ] - vm->stack[ vm->sp + 1 ] );
}
void prose_mul_top( prose_vm_t* vm )
{
	++vm->pc;
	prose_psh( vm, vm->stack[ vm->sp ] * vm->stack[ vm->sp + 1 ] );
}
void prose_div_top( prose_vm_t* vm )
{
	++vm->pc;
	prose_psh( vm, vm->stack[ vm->sp ] / vm->stack[ vm->sp + 1 ] );
}

void prose_pop_off( prose_vm_t* vm )
{
	++vm->pc;
	prose_pop( vm );
}

void print_vm_stack( prose_vm_t* vm )
{
	printf( "Prose VM stack (%llu words):\n", vm->stack_size );
	for ( uint64_t i = 0; i != vm->stack_size; ++i ) {
		printf( "%llu,\n", vm->stack[ i ] );
	}
}

void print_vm_state( prose_vm_t* vm )
{
	printf( "Prose VM state:\n"
			"Stack pointer at %llu\n"
			"Base pointer at %llu\n"
			"Program counter at %llu\n"
			"Cycle counter %llu\n",
			vm->sp, vm->bp, vm->pc, vm->cc );
	print_vm_stack( vm );
}

void prose_execute( prose_vm_t* vm )
{
	vm->cc = 0;
	while ( !vm->escape_condition ) {
		switch ( vm->rom->data[ vm->pc ] ) {
		case PROSE_JMP_REL:
			puts( "jmp rel\n" );
			prose_jmp_rel( vm );
			break;
		case PROSE_PSH_IMM:
			puts( "psh imm\n" );
			prose_psh_imm( vm );
			break;
		case PROSE_POP_OFF:
			puts( "pop off\n" );
			prose_pop_off( vm );
			break;
		case PROSE_ADD_TOP:
			puts( "add top\n" );
			prose_add_top( vm );
			break;
		case PROSE_SUB_TOP:
			puts( "sub top\n" );
			prose_sub_top( vm );
			break;
		case PROSE_MUL_TOP:
			puts( "mul top\n" );
			prose_mul_top( vm );
			break;
		case PROSE_DIV_TOP:
			puts( "div top\n" );
			prose_div_top( vm );
			break;
		case PROSE_HLT_CPU:
			vm->escape_condition = PROSE_COND_HALT;
		default:
			break;	// halt / exception
		}
		// print_vm_state( vm );
		++vm->cc;
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
	print_vm_state( vm );
}
