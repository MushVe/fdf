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

int		get_numbers(char *str, t_linkedlist **list)
{
	int i;
	int number;
	int nb_nb;
	int verif;

	i = 0;
	verif = 0;
	number = 0;
	nb_nb = 0;
	while (str[i])
	{
		if ((ft_isdigit(str[i]) || str[i] == '-' || str[i] == '+')
			&& verif == 0)
		{
			verif = 1;
			number = ft_atoi(str + i);
			nb_nb++;
			new_node(number, list);
		}
		if (str[i] == ' ' || str[i] == '\n')
			verif = 0;
		i++;
	}
	return (nb_nb);
}

int		is_line_valid(char *str)
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

void	parser(char *name, t_param *p, t_linkedlist **list)
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
		if (!is_line_valid(line))
			put_exit("Invalid character in file.");
		p->lenx = get_numbers(line, list);
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
