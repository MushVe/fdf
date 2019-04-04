/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:33:14 by cseguier          #+#    #+#             */
/*   Updated: 2019/04/04 15:14:09 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_exit(char *msg)
{
	ft_putendl(msg);
	exit(0);
}

int		deal_key(int key, void *p)
{
	t_param *tmp;

	tmp = (t_param*)p;
	if (key == 53)
		put_exit("exit ./fdf");
	ft_putchar('x');
	return (0);
}

int		main(int ac, char **av)
{
	t_param	*p;
	char	*map;

	if (ac != 2)
		put_exit("Wrong number of arguments.");
	if (!(p = (t_param*)ft_memalloc(sizeof(t_param))))
		return (0);
	if (!(map = parser(av[1], p)))
		put_exit("error");
	p->info = get_map_info(map, p);
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, W_LEN, W_HEI, "mlx test");
	p->img_ptr = mlx_new_image(p->mlx_ptr, W_LEN, W_HEI);
	p->img_data = mlx_get_data_addr(p->img_ptr,
			&p->bpp, &p->size_line, &p->endian);
	grid(p, -1, -1, -1);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	mlx_key_hook(p->win_ptr, deal_key, p);
	mlx_loop(p->mlx_ptr);
	return (0);
}
