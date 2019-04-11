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
#include <string.h>


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
	p->tx = 350;
	p->ty = 300;
	p->h = 1;
	p->rx = 32;
	p->ry = 16;
}

//void	free_param(t_param *p)
//{
//	ft_memdel((void*)p->info);
//	ft_memdel((void*)img_data);
//	ft_memdel((void*)img_ptr);
//	ft_memdel((void*)mlx_ptr);
//	ft_memdel((void*)win_ptr);
//}

int		main(int ac, char **av)
{
	t_param	p;
	// char	*map;

	// map = NULL;
	linkedlist *list = NULL;
	if (ac != 2)
		put_exit("Wrong number of arguments.");
	// if (!(p = (t_param*)ft_memalloc(sizeof(t_param))))
	// 	return (0);
	parser(av[1], &p, &list);

	int j = 0;
	// while (list) {
	// 	printf("%d | j= %d\n", list->tab, j);
	// 	list = list->next;
	// 	j++;
	// }
	
	// init_param(p);
	// p->info = get_map_info(map, p);

	// int tab[5] = {1,2,3,4,5};
	// linkedlist *list = NULL;

	// for (int i = 0; i < 5; i++) {
	// 	newNode(tab[i], &list);
	// }
	
	// while (list) {
	// 	printf("%d\n", list->tab);
	// 	list = list->next;
	// }

	freeList(&list);

	
	// free(p->info);
	// ft_memdel((void*)map);
//	p->mlx_ptr = mlx_init();
//	p->win_ptr = mlx_new_window(p->mlx_ptr, W_LEN, W_HEI, "fdf");
//	p->img_ptr = mlx_new_image(p->mlx_ptr, W_LEN, W_HEI);
//	p->img_data = mlx_get_data_addr(p->img_ptr, &p->bpp, &p->size_line, &p->e);
//	mlx_key_hook(p->win_ptr, key_hook, p);
//	mlx_expose_hook(p->win_ptr, expose_hook, p);
//	mlx_loop(p->mlx_ptr);
//	free_param(p);
// while(1);
	return (0);
}
