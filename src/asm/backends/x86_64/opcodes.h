#pragma once

#include <stdint.h>

#define X64_MNEM_MAX 32
#define X64_ARG_MAX 4

typedef enum : uint8_t
{
	X64_REG_B,			 // byte
	X64_REG_W,			 // word
	X64_REG_D,			 // dword
	X64_REG_Q,			 // qword
	X64_REG_S,			 // seg
	X64_R_REG = 1 << 7,	 // expanded r-prefix registers (r8-r15) (bitmasked)
} x64_reg_type_t;

typedef struct
{
	const char* name;
	x64_reg_type_t type;
	uint8_t code;
} x64_reg_t;

// typedef enum : uint8_t
// {
// 	FLDS_NO,
// 	//
// } x64_flds_t;

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
	X64_ARG_BA,
	X64_ARG_BB,
	X64_ARG_BD,
	X64_ARG_C,
	X64_ARG_D,
	X64_ARG_E,
	X64_ARG_ES,
	X64_ARG_EST,
	X64_ARG_F,
	X64_ARG_G,
	X64_ARG_H,
	X64_ARG_I,
	X64_ARG_J,
	X64_ARG_M,
	X64_ARG_N,
	X64_ARG_O,
	X64_ARG_P,
	X64_ARG_Q,
	X64_ARG_R,
	X64_ARG_S,
	X64_ARG_SC,
	X64_ARG_T,
	X64_ARG_U,
	X64_ARG_V,
	X64_ARG_W,
	X64_ARG_X,
	X64_ARG_Y,
	X64_ARG_Z,
} x64_arg_profile_t;

/*Wordle 1669 X/6

⬛🟩⬛⬛⬛
⬛🟩⬛⬛⬛
🟨🟩⬛⬛⬛
⬛🟩🟩🟩🟩
⬛🟩🟩🟩🟩
⬛🟩🟩🟩🟩*/

typedef enum : uint8_t
{
	PROC_00,
	PROC_01,
	PROC_02,
	PROC_03,
	PROC_04,
	PROC_P1,
	PROC_PX,
	PROC_PP,
	PROC_P2,
	PROC_P3,
	PROC_P4,
	PROC_C1,
	PROC_C2,
	PROC_C7,
	PROC_IT,
} proc_86_t;

typedef enum : uint8_t
{
	OPMODE_R,
	OPMODE_P,
	OPMODE_E,
	OPMODE_S,
} mode_86_t;

typedef enum : uint8_t
{
	LOCK_L,
	LOCK_S,
	LOCK_p,
	LOCK_P,
} lock_fpup_t;

// typedef enum : uint8_t
// {
// 	GRP_GEN,
// 	GRP_ART,
// } grp_86_t;

// #define NUM_GRP 3

typedef struct
{
	uint8_t pf;
	bool has_0f;
	uint8_t po;
	bool has_so;
	uint8_t so;
	// x64_flds_t flds;
	uint8_t o;
	proc_86_t proc;
	mode_86_t mode;
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
