#include "tok.h"
#include <ctype.h>
#include <string.h>
#include <vcruntime.h>

tok_stream_t create_tok_stream(const char *path)
{
	tok_stream_t out;
	fopen_s(&out.file, path, "rt");
	init_vec(out.macros);

	out.c = fgetc(out.file);

	out.macro_mode = false;

	return out;
}

void fetch_token_file(tok_stream_t *ts)
{
	while (isspace(ts->c))
	{
		ts->c = fgetc(ts->file);
	}
	uint8_t i = 0;
	if (isalnum(ts->c))
	{
		do
		{
			ts->token[i++] = ts->c;
			ts->c = fgetc(ts->file);
		} while (isalnum(ts->c));
	}
	else if (ts->c != EOF)
	{
		ts->token[i++] = ts->c;
		ts->c = fgetc(ts->file);
	}
	ts->token[i] = 0;
}

void fetch_token_macro(tok_stream_t *ts)
{
	if (!strcmp(ts->current_macro->args.data[ts->macro_seeker], "@"))
	{
		// TBD macro arguments
	}
}

macro_t *find_macro(tok_stream_t *ts)
{
	macro_t *macro = NULL;
	for (size_t i = 0; i != ts->macros.size; ++i)
	{
		if (!strcmp(ts->macros.data[i].name, ts->token))
		{
			macro = &ts->macros.data[i];
			break;
		}
	}
	return macro;
}

void fetch_token(tok_stream_t *ts)
{
	if (!ts->macro_mode)
	{
		fetch_token_file(ts);
		ts->current_macro = find_macro(ts);
		if (ts->current_macro)
		{
			ts->macro_seeker = 0;

			goto macro_mode;
		}
	}
	else
	{
	macro_mode:
		fetch_token_macro(ts);
	}
}