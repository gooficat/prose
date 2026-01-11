#include "vm.h"
#include <stdlib.h>

prose_vm_t init_prose_vm( uint64_t stack_size )
{
	prose_vm_t vm;
	vm.bp = 0;
	vm.sp = stack_size;
	vm.stack = malloc( sizeof( uint64_t ) * stack_size );
	vm.rom = NULL;
	return vm;
}

void load_rom( prose_vm_t* vm, prose_rom_t* rom )
{
	vm->rom = rom;
	vm->pc = 0;
}

void prose_execute( prose_vm_t* vm )
{
	switch ( vm->rom->data[ vm->pc ] ) {
	}
}
