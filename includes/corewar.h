/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:38:39 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/12 19:55:19 by wscallop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"

# define OP_CODE_LEN	1
# define ARGS_CODE_LEN	1
# define REG_LEN		1

typedef struct s_cursor	t_cursor;
typedef int32_t			(*t_arg_handler)(t_cursor *cursor, int mode);

typedef struct			s_crw_arguments
{
	int					dump_print_mode;
	int					dump_cycle;
	int					count_players;
	char				*players[MAX_PLAYERS];
}						t_args;

static uint8_t			g_arg_code[3] = {
	T_REG,
	T_DIR,
	T_IND
};

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
	t_qu				cursors;
	size_t				lives_num;
	ssize_t				cycles;
	ssize_t				cycles_to_die;
	ssize_t				cycles_after_check;
	size_t				checks_num;
	t_args				arg;
}						t_vm;

typedef struct			s_op
{
	char				*name;
	uint8_t				code;
	uint8_t				args_num;
	int					args_types_code;
	uint8_t				args_types[3];
	int					modify_carry;
	uint8_t				t_dir_size;
	uint32_t			cycles;
	void				(*func)(t_cursor *);
}						t_op;

struct					s_cursor
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

int32_t					crw_treg(t_cursor *cursor, int mode);
int32_t					crw_tdir(t_cursor *cursor, int mode);
int32_t					crw_tind(t_cursor *cursor, int mode);

static t_arg_handler	g_arg_hands[] =
{
	[1] = crw_treg,
	crw_tdir,
	[4] = crw_tind
};

void					op_live(t_cursor *custor);
void					op_ld(t_cursor *custor);
void					op_st(t_cursor *custor);
void					op_add(t_cursor *custor);
void					op_sub(t_cursor *custor);
void					op_and(t_cursor *custor);
void					op_or(t_cursor *custor);
void					op_xor(t_cursor *custor);
void					op_zjmp(t_cursor *custor);
void					op_ldi(t_cursor *custor);
void					op_sti(t_cursor *custor);
void					op_fork(t_cursor *custor);
void					op_lld(t_cursor *custor);
void					op_lldi(t_cursor *custor);
void					op_lfork(t_cursor *custor);
void					op_aff(t_cursor *custor);

void					dstr_player(t_player *player);
void					invalid_option(t_opt *opt);
void					champ_validation(t_args *args, t_lst *plrs);
int32_t					calc_addr(int32_t addr);
int32_t					bytecode_to_int32(
							const uint8_t *arena, int32_t addr, int32_t size);
void					int32_to_bytecode(uint8_t *arena, int32_t addr,
											int32_t value, int32_t size);
int32_t					get_op_arg(t_cursor *cursor, uint8_t index, int mod);
uint32_t				calc_step(t_cursor *cursor);
t_vm					*crw_init_game(t_vm *vm);
t_player				*create_player(int id);
void					cycles_to_die_check(t_vm *vm);
void					crw_exec(t_vm *vm);
void					init_cursors(t_vm *vm);
t_cursor				*create_cursor(
								t_player *player, int32_t offset, t_vm *vm);
t_cursor				*clone_cursor(t_cursor *cursor);
void					move_cursor(t_cursor *cursor);
uint32_t				step_size(uint8_t arg_type, t_op *op);
int						is_args_valid(t_cursor *cursor);
int						is_arg_types_valid(t_cursor *cursor);
void					parse_types_code(t_cursor *cursor);
t_player				*parse_champion(char *filename, int num);
int8_t					get_byte(t_vm *vm, int32_t offset);
int8_t					check_player_filename(char *filename);
void					parse_args(t_input inp, t_args *args);
int32_t					count_plrs(char **av);
t_lopt					*set_lopt(void);
void					crw_usage(void);
void					print_intro(t_vm *vm);
void					print_awards(t_vm *vm);
void					print_arena(uint8_t *arena);
int						player_cmp(t_player *left, t_player *right);

static t_op				g_op[17] =
{
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

#endif
