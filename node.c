/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:57:07 by cseguier          #+#    #+#             */
/*   Updated: 2019/04/19 18:57:11 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_list(t_linkedlist **list)
{
	t_linkedlist *cpy;
	t_linkedlist *tmp;

	cpy = *list;
	tmp = NULL;
	while (cpy)
	{
		tmp = cpy->next;
		free(cpy);
		cpy = NULL;
		cpy = tmp;
	}
}

void	new_node(int data, t_linkedlist **list)
{
	t_linkedlist *cpy;
	t_linkedlist *node;

	cpy = *list;
	if (!(node = (t_linkedlist*)ft_memalloc(sizeof(t_linkedlist))))
		put_exit("malloc node error");
	if (!cpy)
	{
		node->tab = data;
		node->next = NULL;
		*list = node;
		return ;
	}
	while (cpy->next != NULL)
		cpy = cpy->next;
	node->tab = data;
	node->next = NULL;
	cpy->next = node;
}

int		get_node(int aim, t_param *p)
{
	t_linkedlist	*cpy;
	int				i;

	cpy = p->first;
	i = -1;
	while (++i < aim && cpy)
		cpy = cpy->next;
	return (cpy->tab);
}
