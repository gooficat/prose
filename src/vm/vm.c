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

	--vm->sp;
	if ( vm->sp < 0 ) {
		vm->escape_condition = PROSE_COND_EXCP;
	} else
		vm->stack[ vm->sp ] = val;
}

void prose_jmp_rel( prose_vm_t* vm )
{
	// uint64_t prev_dbg_pc = vm->pc;
	vm->pc += (int8_t)vm->rom->data[ vm->pc + 1 ] +
			  2;  // simulate the pc being at the end of the current
	// printf( "Jumped to %llu from %llu\n", vm->pc, prev_dbg_pc );
}
void prose_psh_imm( prose_vm_t* vm )
{
	++vm->pc;
	prose_psh( vm, *(uint64_t*)&vm->rom->data[ vm->pc ] );
	vm->pc += 8;
}
void prose_pop( prose_vm_t* vm )
{
	// vm->stack[ vm->sp ];
	++vm->sp;
	if ( vm->sp > vm->stack_size ) {
		vm->escape_condition = PROSE_COND_EXCP;
	}
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
	if ( !vm->stack[ vm->sp + 1 ] ) {
		vm->escape_condition = PROSE_COND_EXCP;
	} else
		prose_psh( vm, vm->stack[ vm->sp ] / vm->stack[ vm->sp + 1 ] );
}

void prose_iad_top( prose_vm_t* vm )
{
	++vm->pc;
	prose_psh( vm, (int64_t)vm->stack[ vm->sp ] + vm->stack[ vm->sp + 1 ] );
}
void prose_isb_top( prose_vm_t* vm )
{
	++vm->pc;
	prose_psh( vm, (int64_t)vm->stack[ vm->sp ] - vm->stack[ vm->sp + 1 ] );
}
void prose_iml_top( prose_vm_t* vm )
{
	++vm->pc;
	prose_psh( vm, (int64_t)vm->stack[ vm->sp ] * vm->stack[ vm->sp + 1 ] );
}
void prose_idv_top( prose_vm_t* vm )
{
	++vm->pc;
	if ( !vm->stack[ vm->sp + 1 ] ) {
		vm->escape_condition = PROSE_COND_EXCP;
	} else
		prose_psh( vm, (int64_t)vm->stack[ vm->sp ] / vm->stack[ vm->sp + 1 ] );
}

void prose_pop_off( prose_vm_t* vm )
{
	++vm->pc;
	prose_pop( vm );
}

void prose_swp_stk( prose_vm_t* vm )
{
	++vm->pc;
	uint64_t tmp = vm->stack[ vm->sp ];
	uint64_t si = vm->sp + *(int64_t*)&vm->rom->data[ vm->pc ];
	vm->stack[ vm->sp ] = vm->stack[ si ];
	vm->stack[ si ] = tmp;
	vm->pc += 8;
}

void prose_jmp_ifz( prose_vm_t* vm )
{
	if ( !vm->stack[ vm->sp ] ) {
		prose_jmp_rel( vm );
	}
}
void prose_jmp_ifp( prose_vm_t* vm )
{
	if ( (int64_t)vm->stack[ vm->sp ] > 0 ) {
		prose_jmp_rel( vm );
	}
}
void prose_jmp_ifn( prose_vm_t* vm )
{
	if ( (int64_t)vm->stack[ vm->sp ] < 0 ) {
		prose_jmp_rel( vm );
	}
}

void print_vm_stack( prose_vm_t* vm )
{
	printf( "Prose VM stack (%llu words):\n", vm->stack_size );
	for ( uint64_t i = 0; i != vm->stack_size; ++i ) {
		printf( "%016llx: %llu,\n", i, vm->stack[ i ] );
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
			// puts( "jmp rel\n" );
			prose_jmp_rel( vm );
			break;
		case PROSE_PSH_IMM:
			// puts( "psh imm\n" );
			prose_psh_imm( vm );
			break;
		case PROSE_POP_OFF:
			// puts( "pop off\n" );
			prose_pop_off( vm );
			break;
		case PROSE_ADD_TOP:
			// puts( "add top\n" );
			prose_add_top( vm );
			break;
		case PROSE_SUB_TOP:
			// puts( "sub top\n" );
			prose_sub_top( vm );
			break;
		case PROSE_MUL_TOP:
			// puts( "mul top\n" );
			prose_mul_top( vm );
			break;
		case PROSE_DIV_TOP:
			// puts( "div top\n" );
			prose_div_top( vm );
			break;
		case PROSE_HLT_CPU:
			vm->escape_condition = PROSE_COND_HALT;
			break;
		case PROSE_SWP_STK:
			// puts( "swp stk\n" );
			prose_swp_stk( vm );
			break;
		case PROSE_JMP_IFZ:
			// puts( "jmp ifz\n" );
			prose_jmp_ifz( vm );
			break;
		case PROSE_JMP_IFN:
			// puts( "jmp ifn\n" );
			prose_jmp_ifn( vm );
			break;
		case PROSE_JMP_IFP:
			// puts( "jmp ifp\n" );
			prose_jmp_ifp( vm );
			break;
		case PROSE_IAD_TOP:
			// puts( "iad top\n" );
			prose_iad_top( vm );
			break;
		case PROSE_ISB_TOP:
			// puts( "isb top\n" );
			prose_isb_top( vm );
			break;
		case PROSE_IML_TOP:
			// puts( "iml top\n" );
			prose_iml_top( vm );
			break;
		case PROSE_IDV_TOP:
			// puts( "idv top\n" );
			prose_idv_top( vm );
			break;
		default:
			vm->escape_condition = PROSE_COND_EXCP;
			break;
		}
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
