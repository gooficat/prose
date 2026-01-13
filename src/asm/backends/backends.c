#include "backends.h"
#include <string.h>
#include "prsm/parse.h"
#include "x86_64/parse.h"

const backend_t backends[] = {
	{ "prose", prsm_handle_ins },
	{ "x86_64", x64_asm_handle_ins },
};

const backend_t* current_backend = NULL;

void backend_handle_ins( asm_block_t* bk )
{
	current_backend->handle_ins( bk );
}

void set_backend( const char* name )
{
	for ( uint8_t i = 0; i != sizeof( backends ) / sizeof( backend_t ); ++i )
	{
		if ( !strcmp( name, backends[ i ].name ) )
		{
			current_backend = &backends[ i ];
		}
	}
}
