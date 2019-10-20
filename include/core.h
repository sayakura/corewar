#ifndef CORE_H

# define CORE_H
#include "op.h"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>


// #define MEM_SIZE (4*1024)
// #define REG_NUMBER 16

typedef struct s_cpu
{
    uint8_t		registers[REG_NUMBER + 1];
    uint8_t		*pc;
    uint32_t	rflags;
    // uint8_t      *mar;
    // uint8_t      mdr[16];
}               t_cpu;

typedef struct s_process
{
    t_cpu 				state;
    int32_t      		champ_id;
	struct s_process	*next;
}               t_process;

typedef struct		s_op
{
	char			*name;
	int				argc;
	t_arg_type		argvt[MAX_ARGS_NUMBER];
	char			opcode;
	uint32_t		cycles;
	char			*des;
	bool			coding_byte;
	bool			truncate;
}					t_op;

typedef struct s_champ
{
    int32_t		id;
    char        name[PROG_NAME_LENGTH + 1];
	char        comment[COMMENT_LENGTH + 1];
	uint32_t    prog_size;
	uint32_t    lives;
	uint32_t    last_live;
}               t_champ;

typedef struct 		s_instr
{
	uint8_t			icode;
	uint8_t			acb;
	uint32_t		arg[3];
	uint8_t			arg_t[3];
}					t_instr;

typedef struct		s_hdr
{
	uint32_t		magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	uint32_t		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_hdr;

typedef struct      s_cw
{
	uint32_t		cycle;
	uint32_t		dump_cycle;
	uint32_t 		kill_cycle;
	t_process		*process;
	t_champ			champions[MAX_PLAYERS];
	uint8_t			ownership[MEM_SIZE];
    uint8_t         nplayers;
	int32_t			ctd;
	uint32_t		nbr_live_called;
	uint32_t		checks;
	uint32_t		flags;
}                   t_cw;

t_cpu           g_cpu;
t_cw			g_corewar;
uint8_t			g_ram[MEM_SIZE];
uint8_t         g_gram[MEM_SIZE];

# define F_VERBOSE (1 << 31)

# define R0 g_cpu.registers[0]
# define R1 g_cpu.registers[1]
# define R2 g_cpu.registers[2]
# define R3 g_cpu.registers[3]
# define R4 g_cpu.registers[4]
# define R5 g_cpu.registers[5]
# define R6 g_cpu.registers[6]
# define R7 g_cpu.registers[7]
# define R8 g_cpu.registers[8]
# define R9 g_cpu.registers[9]
# define R10 g_cpu.registers[10]
# define R11 g_cpu.registers[11]
# define R12 g_cpu.registers[12]
# define R13 g_cpu.registers[13]
# define R14 g_cpu.registers[14]
# define R15 g_cpu.registers[15]
# define REG g_cpu.registers

// # define MDR g_cpu.mdr
// # define MAR g_cpu.mar

# define g_op_tab LOOKUP
# define MEM g_ram
# define MEM_END (MEM + MEM_SIZE)
# define LOG printf
# define CORE g_corewar

# define FATAL(msg) ({LOG(msg); exit(1);})


#define PERROR(msg) ({ perror(msg); exit(1); })


extern t_op		g_op_tab[17];

void    ch_load_champ(int fd, uint32_t id, bool assign);
t_champ	*ch_search_champion(int32_t id);
void    ch_champ_intro();

void    h_rev_bytes(void *ptr, size_t n);

void        p_fork(uint8_t *pc, int32_t id, bool before);
void        p_process_loop();
/*
TODO:
using acb as key to dispatch work to different handlers
multiple mov macro
ram memory access

*/


#endif