#pragma once

#include <stdint.h>

#define X64_MNEM_MAX 32
#define X64_ARG_MAX 4

typedef enum : uint8_t
{
	X64_REG_B,
	X64_REG_W,
	X64_REG_D,
	X64_REG_Q,
	X64_R_REG = 1 << 7,	 // expanded r-prefix registers (r8-r15)
} x64_reg_type_t;

typedef struct
{
	const char* name;
	x64_reg_type_t type;
	uint8_t code;
} x64_reg_t;

typedef enum : uint8_t
{
	FLDS_NO,
} x64_flds_t;

typedef struct
{
	const char* name;
	uint16_t idx;  // index in the opcode table
	uint8_t num;   // number of variants
} x64_mnem_t;

typedef enum : uint8_t
{
	X64_N_ARG,
	X64_ARG_A,
} x64_arg_profile_t;

typedef enum : uint8_t
{
	PROC_X64,
} proc_86_t;

typedef enum : uint8_t
{
	OPMODE_N,
} mode_86_t;
typedef enum : uint8_t
{
	RING_NO,
	RING_Z0,
	RING_F1,
	RING_F2,
} ring_86_t;

typedef enum : uint8_t
{
	LOCK_X,
} lock_fpup_t;

typedef enum : uint8_t
{
	GRP_GEN,
	GRP_ART,
} grp_86_t;

// #define NUM_GRP 3

typedef struct
{
	uint8_t pf;
	bool has_0f;
	uint8_t po;
	bool has_so;
	uint8_t so;
	x64_flds_t flds;
	uint8_t o;
	proc_86_t proc;
	mode_86_t mode;
	ring_86_t ring;
	lock_fpup_t lock_fpup;
	x64_arg_profile_t args[ X64_ARG_MAX ];
	// grp_86_t grp[ NUM_GRP ];
} x64_opcode_t;

extern x64_mnem_t mnems[];
extern uint16_t num_mnems;

extern x64_opcode_t opcodes[];
extern uint16_t num_opcodes;

extern x64_reg_t regs[];
extern uint8_t num_regs;
