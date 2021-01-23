/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscallop <wscallop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:39:51 by wscallop          #+#    #+#             */
/*   Updated: 2021/01/21 23:11:36 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../libft/includes/libft.h"
# include "op.h"


/*
** Macroses
*/

# define OP_CODE_LEN	1
# define ARGS_CODE_LEN	1
# define REG_LEN		1

/*
** Log Levels
*/

# define LIVE_LOG			1
# define CYCLE_LOG			2
# define OP_LOG				4
# define DEATH_LOG			8
# define PC_MOVEMENT_LOG	16

/*
** Arg's type — Arg's code
*/

typedef struct			s_opt
{
	int					out;
	int					color;
	int					req;
	int					pth;
}						t_opt;

typedef struct			s_corewar_arguments
{
	int 				dump;
	int 				players_count;
	t_lst 				*players;
	t_pair
}						t_arg;

//static uint8_t			g_arg_code[3] = {
//	T_REG,
//	T_DIR,
//	T_IND
//};

/*
** Player
*/

/*
** id                 — id number of player
** name               — champion's name
** comment            — champion's comment
** code_size          — size of champion's executable code
** code               — champion's executable code
** current_lives_num  — number of reports that player is alive
**                      during current cycles_to_die period
** previous_lives_num — number of reports that player is alive
**                      during previous cycles_to_die period
** last_live          — cycle's number, on which player was assigned
**                      as alive last time
*/

typedef struct			s_player
{
	int32_t				id;
	char				*name;
	char				*comment;
	int32_t				code_size;
	uint8_t				*code;
	size_t				current_lives_num;
	size_t				previous_lives_num;
	ssize_t				last_live;
}						t_player;

/*
** Cursor
*/

/*
** id             — id number of cursor
** carry          — special flag
** op_code        — operator's code that is placed under cursor
** last_live      — cycle's number when live operator was executed last time
** till_exec — number of cycles that remains to wait
** args_types     - types of op's each argument
**                  before operator execution
** offset             — address of the next operator to execute at memory
** step           — number of bytes to shift
** reg            — registers
** player         — owner of cursor
*/

typedef struct			s_cursor
{
	uint32_t			id;
	int					carry;
	t_op				*op;
	ssize_t				last_live;
	int					till_exec;
	uint8_t				args_types[3];
	int32_t				offset;
	uint32_t			step;
	int32_t				reg[REG_NUMBER];
	t_player			*player;
//	struct s_cursor		*next;
}						t_cursor;

/*
** Virtual machine
*/

/*
** arena              — memory where players are fighting
** players            — list of players
** players_num        — number of players
** last_alive         — pointer to the last player that was assigned as alive
** cursors            — list of cursors
** cursors_num        — number of cursors
** lives_num          — number of executed live operators during of cycle_to_die
** cycles             — number of cycles that was passed after start
** cycles_to_die      — game parameter
** cycles_after_check — number of cycles that was passed after last rules check
** checks_num         — game parameter
** vs                 — visualizer
** dump_cycle         — cycle's number after which dump of arena will be created
** dump_print_mode    — print mode of dump (32/64 bytes per line)
** show_cycle         — number of cycles after which arena will be shown
** show_print_mode    — print mode of show (32/64 bytes per line)
** display_aff        — flag that reports display output of aff operator or not
** log                — number that reports about log level.
**                      If log is assigned as -1, it means that log doesn't
**                      display.
*/

typedef struct			s_vm
{
	uint8_t				arena[MEM_SIZE];
	t_lst				players;
	int32_t				players_num;
	t_player			*last_alive;
	t_qu 				cursors;
//	size_t				cursors_num;
	size_t				lives_num;
	ssize_t				cycles;
	ssize_t				cycles_to_die;
	ssize_t				cycles_after_check;
	size_t				checks_num;
	ssize_t				dump_cycle;
	int					dump_print_mode;
	ssize_t				show_cycle;
	int					show_print_mode;
	t_opt 				opt;
}						t_vm;

typedef struct	s_op
{
	char		*name;
	uint8_t		code;
	uint8_t		args_num;
	int 		args_types_code;
	uint8_t		args_types[3];
	int			modify_carry;
	uint8_t		t_dir_size;
	uint32_t	cycles;
	void		(*func)(t_vm *, t_cursor *);

}				t_op;

static t_op		g_op[16] = {
		[0x01] =
		{
				.name = "live",
				.code = 0x01,
				.args_num = 1,
				.args_types_code = false,
				.args_types = {T_DIR, 0, 0},
				.modify_carry = false,
				.t_dir_size = 4,
				.cycles = 10,
				.func = &op_live
		},
		{
				.name = "ld",
				.code = 0x02,
				.args_num = 2,
				.args_types_code = true,
				.args_types = {T_DIR | T_IND, T_REG, 0},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 5,
				.func = &op_ld
		},
		{
				.name = "st",
				.code = 0x03,
				.args_num = 2,
				.args_types_code = true,
				.args_types = {T_REG, T_REG | T_IND, 0},
				.modify_carry = false,
				.t_dir_size = 4,
				.cycles = 5,
				.func = &op_st
		},
		{
				.name = "add",
				.code = 0x04,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG, T_REG, T_REG},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 10,
				.func = &op_add
		},
		{
				.name = "sub",
				.code = 0x05,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG, T_REG, T_REG},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 10,
				.func = &op_sub
		},
		{
				.name = "and",
				.code = 0x06,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 6,
				.func = &op_and
		},
		{
				.name = "or",
				.code = 0x07,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 6,
				.func = &op_or
		},
		{
				.name = "xor",
				.code = 0x08,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 6,
				.func = &op_xor
		},
		{
				.name = "zjmp",
				.code = 0x09,
				.args_num = 1,
				.args_types_code = false,
				.args_types = {T_DIR, 0, 0},
				.modify_carry = false,
				.t_dir_size = 2,
				.cycles = 20,
				.func = &op_zjmp
		},
		{
				.name = "ldi",
				.code = 0x0A,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
				.modify_carry = false,
				.t_dir_size = 2,
				.cycles = 25,
				.func = &op_ldi
		},
		{
				.name = "sti",
				.code = 0x0B,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
				.modify_carry = false,
				.t_dir_size = 2,
				.cycles = 25,
				.func = &op_sti
		},
		{
				.name = "fork",
				.code = 0x0C,
				.args_num = 1,
				.args_types_code = false,
				.args_types = {T_DIR, 0, 0},
				.modify_carry = false,
				.t_dir_size = 2,
				.cycles = 800,
				.func = &op_fork
		},
		{
				.name = "lld",
				.code = 0x0D,
				.args_num = 2,
				.args_types_code = true,
				.args_types = {T_DIR | T_IND, T_REG, 0},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 10,
				.func = &op_lld
		},
		{
				.name = "lldi",
				.code = 0x0E,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
				.modify_carry = true,
				.t_dir_size = 2,
				.cycles = 50,
				.func = &op_lldi
		},
		{
				.name = "lfork",
				.code = 0x0F,
				.args_num = 1,
				.args_types_code = false,
				.args_types = {T_DIR, 0, 0},
				.modify_carry = false,
				.t_dir_size = 2,
				.cycles = 1000,
				.func = &op_lfork
		},
		{
				.name = "aff",
				.code = 0x10,
				.args_num = 1,
				.args_types_code = true,
				.args_types = {T_REG, 0, 0},
				.modify_carry = false,
				.t_dir_size = 4,
				.cycles = 2,
				.func = &op_aff
		}
};

/*
** Init
*/

t_player				*init_player(int id);

t_cursor				*init_cursor(t_player *player, int32_t pc);

t_vm					*init_vm(void);

void					init_arena(t_vm *vm);

/*
** Parse
*/

void					parse_corewar_args(int argc, char **argv, t_vm *vm);

void					parse_vs_flag(int *argc, char ***argv, t_vm *vm);

void					parse_dump_flag(int *argc, char ***argv, t_vm *vm);

void					parse_show_flag(int *argc, char ***argv, t_vm *vm);

void					parse_aff_flag(int *argc, char ***argv, t_vm *vm);

void					parse_log_flag(int *argc, char ***argv, t_vm *vm);
t_lst					champs_validation(t_lst *corewar_args);
t_player				*parse_champion(char *filename, int num);

/*
** Cursor
*/

void					set_cursors(t_vm *vm);

void					add_cursor(t_cursor **list, t_cursor *new);

/*
** Execute
*/

void					exec(t_vm *vm);

void					exec_cycle(t_vm *vm);

/*
** Execute Utils
*/

void					update_op_code(t_vm *vm, t_cursor *current);

void					move_cursor(t_vm *vm, t_cursor *cursor);

void					free_vm(t_vm **vm);

/*
** Utils
*/

int32_t					calc_addr(int32_t addr);

int8_t					get_byte(t_vm *vm, int32_t pc, int32_t step);

void					cycles_to_die_check(t_vm *vm);

/*
** Print
*/

void					print_intro(t_player **players, int32_t players_num);

void					print_last_alive(t_vm *vm);

void					print_help();

void					print_arena(uint8_t *arena, int print_mode);

/*
** Log
*/

void					log_cycle(ssize_t cycle);

void					log_pc_movements(uint8_t *arena, t_cursor *cursor);

void					log_cursor_death(t_vm *vm, t_cursor *cursor);

void					log_cycles_to_die(ssize_t cycles_to_die);

# endif