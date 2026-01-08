#pragma once

#define class(n)                                                                                                       \
	typedef struct n n;                                                                                                \
	struct n

#define enum(n, t)                                                                                                     \
	typedef t n;                                                                                                       \
	enum n

#define union(n)                                                                                                       \
	typedef union n n;                                                                                                 \
	union n