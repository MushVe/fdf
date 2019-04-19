/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:29:16 by cseguier          #+#    #+#             */
/*   Updated: 2019/04/11 17:31:52 by cseguier         ###   ########.fr       */
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

// int		*get_map_info(t_param *p)
// {
// 	// int		i;
// 	// int		*res;
// 	// char	**tmp;

// 	int *tab = malloc(sizeof(int) * 9);
// 	tab[0] = 0;
// 	tab[1] = 0;
// 	tab[2] = 0;
// 	tab[3] = 0;
// 	tab[4] = 0;
// 	tab[5] = 1;
// 	tab[6] = 0;
// 	tab[7] = 0;
// 	tab[8] = 0;
	

// 	// p->len_map = no_newline(map, p);
// 	// if (!(res = (int*)ft_memalloc(sizeof(int) * (p->len_map + 1))))
// 	// 	put_exit("get_map_info malloc fail");
// 	// if (!(tmp = ft_strsplit(map, ' ')))
// 	// 	put_exit("tmp info split fail");
// 	// i = -1;
// 	// while (++i < p->len_map)
// 	// {
// 	// 	if (ft_atoi(tmp[i]) > p->i_max)
// 	// 		p->i_max = ft_atoi(tmp[i]);
// 	// 	if (ft_atoi(tmp[i]) < p->i_min)
// 	// 		p->i_min = ft_atoi(tmp[i]);
// 	// 	res[i] = ft_atoi(tmp[i]);
// 	// }
// 	// res[i] = 0;
// 	// i = -1;
// //	while (++i < p->len_map)
// //		ft_memdel((void*)tmp[i]);
// //	ft_memdel((void*)tmp);
// 	return (tab);
// }

int	getNumbers(char *str, linkedlist **list)
{
	int i;
	int numberToGet;
	int nb_nb;

	i = 0;
	numberToGet = 0;
	nb_nb = 0;
	newNode(ft_atoi(str), list);
	nb_nb++;
	while (str[i])
	{
		// if non valide, si plusieurs espaces d'afffile
		if (str[i] == ' ')
		{
			numberToGet = ft_atoi(str + i);
			nb_nb++;
			newNode(numberToGet, list);
		}
		i++;
	}
	return (nb_nb);
}

int isLineValid(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\n'
			&& !ft_isdigit(str[i]) && str[i] != '+'
			&& str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}


void	parser(char *name, t_param *p, linkedlist **list)
{
	int		fd;
	char	*line;
	int		i;
	int		length;

	i = 1;
	line = NULL;
	p->size_line = 0;
	if (0 > (fd = open(name, O_RDONLY)))
		put_exit("open error");
	while (0 < (i = get_next_line(fd, &line)))
	{
		if (!isLineValid(line))
			put_exit("Invalid character in file.");
	 	p->lenx = getNumbers(line, list);
		if (length != 0 && p->lenx != length)
		 	put_exit("Irregular width in file.");
		length = p->lenx;
		p->leny++;
		free(line);
	}
	if (i < 0)
		put_exit("gnl error");
	p->first = *list;
}
