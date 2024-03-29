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
#include <math.h>
#include <limits.h>

// #define MEM_SIZE (4*1024)
// #define REG_NUMBER 16

typedef struct	s_reg
{
	int32_t		registers[REG_NUMBER + 1];
	int32_t		pc; // + 1
	int32_t		rdi; // + 2
	int32_t		rsi; // + 3
	int32_t		rcx; // + 4
	int32_t		val_e; // + 5 
	int32_t		val_p; // + 6 
}				t_reg;

typedef union u_reg
{
	t_reg	sreg;
	int32_t	ureg[sizeof(t_reg) / sizeof(int32_t)];
}				tu_reg;

typedef struct s_cpu
{
	tu_reg 		registers;
	uint8_t		acb;
    uint32_t	rflags;
	bool		write_back: 1;
    // uint8_t      *mar;
    // uint8_t      mdr[16];
}               t_cpu;

typedef struct s_process
{
    t_cpu 				state;
    int32_t      		champ_id;
	uint32_t			last_live;
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
	uint32_t		nprocess;
	t_champ			champions[MAX_PLAYERS];
	uint8_t			ownership[MEM_SIZE];
    uint8_t         nplayers;
	uint32_t		cycle_to_die;
	uint32_t		nbr_live_called;
	uint32_t		checks;
	uint32_t		flags;
}                   t_cw;

t_cpu           g_cpu;
t_cw			g_corewar;
uint8_t			g_ram[MEM_SIZE];
uint8_t         g_gram[MEM_SIZE];


# define CPU_STATE g_cpu
# define F_VERBOSE (1 << 31)

# define PC_V g_cpu.registers.sreg.pc
# define PC (REG_NUMBER + 1)
# define RDI (REG_NUMBER + 2)
# define RSI (REG_NUMBER + 3)
# define RCX (REG_NUMBER + 4)
# define VAL_E (REG_NUMBER + 5) 
# define VAL_P (REG_NUMBER + 6) 
# define ACB (g_cpu.acb)
// shit these are bull shit
# define R0 0
# define R1 1
# define R2 2
# define R3 3
# define R4 4
# define R5 5
# define R6 6
# define R7 7
# define R8 8
# define R9 9
# define R10 10
# define R11 11
# define R12 12
# define R13 13
# define R14 14
# define R15 15
# define REG g_cpu.registers.ureg

// # define MDR g_cpu.mdr
// # define MAR g_cpu.mar

# define LOOKUP g_op_tab 
# define MEM g_ram
# define MEM_END (MEM + MEM_SIZE)
# define LOG printf
# define CORE g_corewar
# define FATAL(msg) ({LOG(msg); exit(1);})
# define PUSH 1
# define POP 0
# define PC_UPDATE(p, vp) (p = vp % MEM_SIZE) 
# define WRITE_BACK(nreg, val_e) (REG[nreg] = val_e)
#define PERROR(msg) ({ perror(msg); exit(1); })


extern t_op		g_op_tab[17];

void    ch_load_champ(int fd, uint32_t id, bool assign);
t_champ	*ch_search_champion(int32_t id);
void    ch_champ_intro();

void    h_rev_bytes(void *ptr, size_t n);

void        p_fork(uint32_t pc, int32_t id, bool before);
void        p_process_loop();


void    cw_start();


void	ft_putchar(char c);
void	h_puthex(unsigned char c);
void    i_instruction_cycle();
/*
TODO:
using acb as key to dispatch work to different handlers
multiple mov macro
ram memory access

*/


#endif