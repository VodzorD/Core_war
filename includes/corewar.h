/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscallop <wscallop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:39:51 by wscallop          #+#    #+#             */
/*   Updated: 2021/01/27 22:29:32 by jpasty           ###   ########.ru       */
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

//typedef struct			s_opt
//{
//	int					out;
//	int					color;
//	int					req;
//	int					pth;
//}						t_opt;

typedef struct			s_corewar_arguments
{
	int 				dump;
	int 				players_count;
	t_lst 				*players;
}						t_arg;

static uint8_t			g_arg_code[3] = {
	T_REG,
	T_DIR,
	T_IND
};

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
	ssize_t				last_live;
}						t_player;

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

typedef struct s_cursor t_cursor;

typedef int32_t		(*t_arg_handler)(t_cursor *cursor, int mode);

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
	void		(*func)(t_cursor *);

}				t_op;

struct			s_cursor
{
	t_vm				*vm;
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
};

int32_t			crw_treg(t_cursor *cursor, int mode);
int32_t			crw_tdir(t_cursor *cursor, int mode);
int32_t			crw_tind(t_cursor *cursor, int mode);

static t_arg_handler	g_arg_hands[] = {
		crw_treg,
		crw_tdir,
		[3] = crw_tind
};


void			op_live(t_cursor *custor);
void			op_ld(t_cursor *custor);
void			op_st(t_cursor *custor);
void			op_add(t_cursor *custor);
void			op_sub(t_cursor *custor);
void			op_and(t_cursor *custor);
void			op_or(t_cursor *custor);
void			op_xor(t_cursor *custor);
void			op_zjmp(t_cursor *custor);
void			op_ldi(t_cursor *custor);
void			op_sti(t_cursor *custor);
void			op_fork(t_cursor *custor);
void			op_lld(t_cursor *custor);
void			op_lldi(t_cursor *custor);
void			op_lfork(t_cursor *custor);
void			op_aff(t_cursor *custor);

static t_op		g_op[17] = {
		[0x01] =
		{
				.name = "live",
				.code = 0x01,
				.args_num = 1,
				.args_types_code = 0,
				.args_types = {T_DIR, 0, 0},
				.modify_carry = 0,
				.t_dir_size = 4,
				.cycles = 10,
				.func = &op_live
		},
		{
				.name = "ld",
				.code = 0x02,
				.args_num = 2,
				.args_types_code = 1,
				.args_types = {T_DIR | T_IND, T_REG, 0},
				.modify_carry = 1,
				.t_dir_size = 4,
				.cycles = 5,
				.func = &op_ld
		},
		{
				.name = "st",
				.code = 0x03,
				.args_num = 2,
				.args_types_code = 1,
				.args_types = {T_REG, T_REG | T_IND, 0},
				.modify_carry = 0,
				.t_dir_size = 4,
				.cycles = 5,
				.func = &op_st
		},
		{
				.name = "add",
				.code = 0x04,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG, T_REG, T_REG},
				.modify_carry = 1,
				.t_dir_size = 4,
				.cycles = 10,
				.func = &op_add
		},
		{
				.name = "sub",
				.code = 0x05,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG, T_REG, T_REG},
				.modify_carry = 1,
				.t_dir_size = 4,
				.cycles = 10,
				.func = &op_sub
		},
		{
				.name = "and",
				.code = 0x06,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.modify_carry = 1,
				.t_dir_size = 4,
				.cycles = 6,
				.func = &op_and
		},
		{
				.name = "or",
				.code = 0x07,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.modify_carry = 1,
				.t_dir_size = 4,
				.cycles = 6,
				.func = &op_or
		},
		{
				.name = "xor",
				.code = 0x08,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.modify_carry = 1,
				.t_dir_size = 4,
				.cycles = 6,
				.func = &op_xor
		},
		{
				.name = "zjmp",
				.code = 0x09,
				.args_num = 1,
				.args_types_code = 0,
				.args_types = {T_DIR, 0, 0},
				.modify_carry = 0,
				.t_dir_size = 2,
				.cycles = 20,
				.func = &op_zjmp
		},
		{
				.name = "ldi",
				.code = 0x0A,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
				.modify_carry = 0,
				.t_dir_size = 2,
				.cycles = 25,
				.func = &op_ldi
		},
		{
				.name = "sti",
				.code = 0x0B,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
				.modify_carry = 0,
				.t_dir_size = 2,
				.cycles = 25,
				.func = &op_sti
		},
		{
				.name = "fork",
				.code = 0x0C,
				.args_num = 1,
				.args_types_code = 0,
				.args_types = {T_DIR, 0, 0},
				.modify_carry = 0,
				.t_dir_size = 2,
				.cycles = 800,
				.func = &op_fork
		},
		{
				.name = "lld",
				.code = 0x0D,
				.args_num = 2,
				.args_types_code = 1,
				.args_types = {T_DIR | T_IND, T_REG, 0},
				.modify_carry = 1,
				.t_dir_size = 4,
				.cycles = 10,
				.func = &op_lld
		},
		{
				.name = "lldi",
				.code = 0x0E,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
				.modify_carry = 1,
				.t_dir_size = 2,
				.cycles = 50,
				.func = &op_lldi
		},
		{
				.name = "lfork",
				.code = 0x0F,
				.args_num = 1,
				.args_types_code = 0,
				.args_types = {T_DIR, 0, 0},
				.modify_carry = 0,
				.t_dir_size = 2,
				.cycles = 1000,
				.func = &op_lfork
		},
		{
				.name = "aff",
				.code = 0x10,
				.args_num = 1,
				.args_types_code = 1,
				.args_types = {T_REG, 0, 0},
				.modify_carry = 0,
				.t_dir_size = 4,
				.cycles = 2,
				.func = &op_aff
		}
};


int32_t		calc_addr(int32_t addr);

int32_t		bytecode_to_int32(const uint8_t *arena, int32_t addr, int32_t size);

void		int32_to_bytecode(uint8_t *arena, int32_t addr, int32_t value,
							  int32_t size);
int32_t		get_op_arg(t_cursor *cursor, uint8_t index, int mod);
uint32_t	calc_step(t_cursor *cursor);
t_vm					*crw_init_game(t_vm *vm);
t_player		*create_player(int id);
void			cycles_to_die_check(t_vm *vm);
void			crw_exec(t_vm *vm);
void			init_cursors(t_vm *vm);
t_cursor	*create_cursor(t_player *player, int32_t offset, t_vm *vm);
t_cursor		*clone_cursor(t_cursor *cursor);
void				move_cursor(t_cursor *cursor);
uint32_t			step_size(uint8_t arg_type, t_op *op);
int					is_args_valid(t_cursor *cursor);
int 				is_arg_types_valid(t_cursor *cursor); //TODO check
void				parse_types_code(t_cursor *cursor);
t_player				*parse_champion(char *filename, int num);
int32_t					calc_addr(int32_t addr);
int8_t					get_byte(t_vm *vm, int32_t offset);
void					cycles_to_die_check(t_vm *vm);
t_lst				champ_validation(t_lst *corewar_args);
int8_t 		check_player_filename(char *filename);
t_lst		*parse_options(int ac, char **av, t_vm *vm);
t_lst 		*collect_args(t_vm **vm, t_input inp, t_qu *queue);

# endif