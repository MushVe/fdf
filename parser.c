/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:29:16 by cseguier          #+#    #+#             */
/*   Updated: 2019/04/03 17:45:40 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		no_newline(char *map, t_param *param)
{
	int	i;

	i = -1;
	while (map[++i])
		if (map[i] == '\n')
			map[i] = ' ';
	return (param->lenx * param->leny);
}

int		*get_map_info(char *map, t_param *param)
{
	int		i;
	int		*res;
	char	**tmp;

	param->len_map = no_newline(map, param);
	if (!(res = (int*)ft_memalloc(sizeof(int) * (param->len_map + 1))))
		put_exit("get_map_info malloc fail");
	if (!(tmp = ft_strsplit(map, ' ')))
		put_exit("tmp info split fail");
	i = -1;
	while (++i < param->len_map)
		res[i] = ft_atoi(tmp[i]);
	res[i] = 0;
	return (res);
}

int		get_lenx(char *map)
{
	int	i;
	int	cpt;
	int	check;

	i = -1;
	cpt = 0;
	check = 0;
	while (map[++i] != '\n' && map[i] != '\0')
	{
		if (ft_isdigit(map[i]))
		{
			if (check == 0)
				cpt++;
			check++;
		}
		if (map[i] == ' ')
			check = 0;
	}
	return (cpt);
}

int		get_leny(char *map)
{
	int	i;
	int	cpt;

	i = -1;
	cpt = 0;
	while (map[++i] != '\0')
		if (map[i] == '\n')
			cpt++;
	return (cpt);
}

char	*parser(char *name, t_param *param)
{
	int		fd;
	char	*line;
	char	*map;
	int		i;

	i = 1;
	param->size_line = 0;
	if (0 > (fd = open(name, O_RDONLY)))
		put_exit("open error");
	map = "\0";
	while (0 < (i = get_next_line(fd, &line)))
	{
		if (param->size_line == 0)
			param->size_line = get_lenx(line);
		if (param->size_line != get_lenx(line))
			put_exit("non valid file");
		if (!(map = ft_strjoin(map, line, 0)))
			put_exit("fail join line");
		if (!(map = ft_strjoin(map, "\n", 0)))
			put_exit("fail join newline");
	}
	param->lenx = get_lenx(map);
	param->leny = get_leny(map);
	return (map);
}
