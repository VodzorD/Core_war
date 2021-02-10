
#include "corewar.h"
static t_player	*check_plr(size_t id, char *plr_filename);
static uint32_t	validate_num(uint8_t **bytes, size_t size);
static char		*validate_str(uint8_t **bytes, size_t len);
static uint8_t	*validate_code(int fd, uint32_t prog_size);

int			champ_validation(t_args *args, t_lst *plrs)
{
	int			i;

	i = 0;
	while (i < args->count_players)
	{
		lst_prepend(plrs, check_plr(i + 1, args->players[i]));
		i++;
	}
	return (1);
}

static t_player	*check_plr(size_t id, char *plr_filename)
{
	int 		fd;
	static uint8_t 	hdr[sizeof(header_t)];
	t_player	*plr;
	uint8_t		*hdd;
	hdd = hdr;

	ft_bzero(hdr, sizeof(header_t));
	if (!(plr = ft_memalloc(sizeof(t_player))))
		ft_error("Alloc err", -1);
	plr->id = id;
	if ((fd = open(plr_filename, O_RDONLY)) == -1)
		ft_error("Cannot open file", -1);
	if (read(fd, hdr, sizeof(header_t)) != sizeof(header_t))
		ft_error("reading error", -1);
	if (validate_num( &hdd, sizeof(COREWAR_EXEC_MAGIC)) != COREWAR_EXEC_MAGIC)
		ft_error("MAGIC doesn't exist!", -1);
	if (!(plr->name = validate_str(&hdd, PROG_NAME_LENGTH)))
		ft_error("Champ name error!", -1);
	if ((plr->code_size = validate_num((uint8_t **) &hdd, sizeof(uint32_t))) == -1)
			ft_error("Wrong code size!", -1);
	if (!(plr->comment = validate_str(&hdd, COMMENT_LENGTH)))
				ft_error("Champ comment error!", -1);
	if (!(plr->code = validate_code(fd, plr->code_size)))
		ft_error("Code doesn't match code size", -1);
	return (plr);
}
static uint8_t	*validate_code(int fd, uint32_t prog_size)
{
	uint8_t 	*code;
	uint8_t		eof;

	if (!(code = malloc(sizeof(uint8_t) * prog_size)))
		return (NULL);
	if (read(fd, code, prog_size) != prog_size)
		return (NULL);
	if (read(fd, &eof, 1) != 0)
		return (NULL);
	return (code);
}

static char		*validate_str(uint8_t **bytes, size_t len)
{
	char		*ret;
	size_t		i;
	size_t		offset;

	i = 0;
	offset = len;
	while (i < 4)
		if ((*bytes)[len + i++] != 0)
			return NULL;
	if (!(ret = malloc(sizeof(char) * len)))
		return NULL;
	while (len--)
		ret[len] = (*bytes)[len];
	*bytes += (offset + 4);
	return (ret);
}

static uint32_t	validate_num(uint8_t **bytes, size_t size)
{
	uint32_t 	num;
	size_t		i;

	num = 0x00;
	i = 0;
	if (size > sizeof(uint32_t))
		return 0;
	if (*bytes[0] == 0xff)
		return -1;
	while ((*bytes)[i] == 0x00)
		if (i++ >= size)
			return -1;
	while (i < size)
	{
		num += (*bytes)[i];
		if (++i < size)
			num <<= 8;
	}
	*bytes += size;
	return num;
}