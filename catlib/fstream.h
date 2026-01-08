#pragma once

#include <stdio.h>

#include "class.h"
#include "types.h"

class(FStream)
{
	FILE *file;
	i16 buffer;
};

#define fsgetc(fs) (fs).buffer = fgetc((fs).file);

#define init_stream(fs, path)                                                                                          \
	fopen_s(&(fs).file, path, "rt");                                                                                   \
	fsgetc(fs);

#define rewind_stream(fs)                                                                                              \
	rewind((fs).file);                                                                                                 \
	fsgetc(fs);