/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:33:14 by cseguier          #+#    #+#             */
/*   Updated: 2019/04/11 18:28:20 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	put_exit(char *msg)
{

	ft_putendl(msg);
	exit(0);
}

void freeList(linkedlist **list)
{
	linkedlist *cpy = *list;
	linkedlist *tmp = NULL;

	while (cpy) {
		tmp = cpy->next;
		free(cpy);
		cpy = NULL;
		cpy = tmp;
	}

}

void newNode(int data, linkedlist **list)
{
	linkedlist *cpy = *list;

	if (!cpy) {
		linkedlist *node = malloc(sizeof(linkedlist));
		node->tab = data;
		node->next = NULL;

		*list = node;
		
		return ;
	}
	
	while (cpy->next != NULL) {
		cpy = cpy->next;
	}

	linkedlist *newNode = malloc(sizeof(linkedlist));
	newNode->tab = data;
	newNode->next = NULL;

	cpy->next = newNode;
}


void	init_param(t_param *p)
{
	p->i_max = 0;
	p->i_min = 0;
	p->lenx = 0;
	p->leny = 0;
	p->tx = 350;
	p->ty = 300;
	p->h = 1;
	p->rx = 32;
	p->ry = 16;
}


// void	setTab(t_param *p, linkedlist **list)
// {
// 	linkedlist	*cpy;
// 	int			i;

// 	i = 0;
// 	if (!(p->tab = (int*)ft_memalloc(sizeof(int) * (p->lenx * (p->leny + 1)))))
// 		put_exit("setTab malloc fail.");
// 	cpy = p->first;
// 	while (cpy)
// 	{
// 		p->tab[i] = cpy->tab;
// 		cpy = cpy->next;
// 		i++;
// 	}
// 	while (p->tab[i])
// 	{
// 		p->tab[i] = 0;
// 		i++;
// 	}
// }

int		main(int ac, char **av)
{
	t_param		p;
	linkedlist	*list;

	list = NULL;
	if (ac != 2)
		put_exit("Wrong number of arguments.");
	init_param(&p);
	parser(av[1], &p, &list);
//	p.first = &list;

	linkedlist *cpy;
	cpy = p.first;
	while (cpy)
	{
		ft_putnbr(cpy->tab); ft_putchar(' ');
		cpy = cpy->next;
	}
	ft_putendl("");
	ft_putnbr(p.lenx); ft_putchar('\t');
	ft_putnbr(p.leny); ft_putendl("");

	//setTab(&p, &list);

	freeList(&list);

	p.mlx_ptr = mlx_init();
	p.win_ptr = mlx_new_window(p.mlx_ptr, W_LEN, W_HEI, "fdf");
	p.img_ptr = mlx_new_image(p.mlx_ptr, W_LEN, W_HEI);
	p.img_data = mlx_get_data_addr(p.img_ptr, &p.bpp, &p.size_line, &p.e);
	mlx_key_hook(p.win_ptr, key_hook, &p);
	mlx_expose_hook(p.win_ptr, expose_hook, &p);
	mlx_loop(p.mlx_ptr);
	return (0);
}