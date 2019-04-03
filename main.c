/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:33:14 by cseguier          #+#    #+#             */
/*   Updated: 2019/04/03 18:51:58 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_exit(char *msg)
{
	ft_putendl(msg);
	exit(0);
}

void	bresenham(t_param *p, int xi, int yi, int xf, int yf)
{
	int i;
	int x;
	int y;

	x = xi;
	y = yi;
	p->dx = xf - xi;
	p->dy = yf - yi;
	p->x_i = (p->dx > 0) ? 1 : -1;
	p->y_i = (p->dy > 0) ? 1 : -1;
	p->dx = abs(p->dx);
	p->dy = abs(p->dy);
	i = 0;
	if (p->dx > p->dy)
	{
		p->cpt = p->dx / 2;
		while (++i <= p->dx)
		{
			x += p->x_i;
			p->cpt += p->dy;
			if (p->cpt >= p->dx)
			{
				p->cpt -= p->dx;
				y += p->y_i;
			}
			if (x <= W_LEN - 1 && y <= W_HEI - 1 && x >= 0 && y >= 0)
			{
				p->incr = (((y * W_HEI) + x) * 4);
				p->img_data[p->incr] = 0x00;
				p->img_data[p->incr + 1] = 0xDE;
				p->img_data[p->incr + 2] = 0xFF;
				p->img_data[p->incr + 3] = 0x00;
			}
		}
	}
	else
	{
		p->cpt = p->dy / 2;
		while (++i <= p->dy)
		{
			y += p->y_i;
			p->cpt += p->dx;
			if (p->cpt >= p->dy)
			{
				p->cpt -= p->dy;
				x += p->x_i;
			}
			if (x <= W_LEN - 1 && y <= W_HEI - 1 && x >= 0 && y >= 0)
			{
				p->incr = (((y * W_HEI) + x) * 4);
				p->img_data[p->incr] = 0x00;
				p->img_data[p->incr + 1] = 0xDE;
				p->img_data[p->incr + 2] = 0xFF;
				p->img_data[p->incr + 3] = 0x00;
			}
		}
	}
}

void	grid(t_param *p)
{
	int	x;
	int	y;
	int	mapx;
	int	mapy;
	int i;

	mapx = -1;
	mapy = -1;
	x = 0;
	y = 0;
	i = -1;
	while (++mapy < p->leny)
	{
		while (++mapx < p->lenx)
		{
			++i;
			x = 350 + (mapx - mapy) * 32;
			y = 300 - (p->info[i])
				+ (mapx + mapy) * 16;
			if (x <= W_LEN && x >= 0 && y <= W_HEI && y >= 0)
			{
				p->incr = ((y * W_HEI) + x) * 4;
				p->img_data[p->incr] = 0xFF;
				p->img_data[p->incr + 1] = 0xFF;
				p->img_data[p->incr + 2] = 0xFF;
				p->img_data[p->incr + 3] = 0x00;
			}
			if (mapx < p->lenx - 1)
				bresenham(p, x, y, 350 + (mapx - mapy + 1) * 32,
					300 - (p->info[i + 1])
						+ (mapx + mapy + 1) * 16);
			if (mapy < p->leny - 1)
				bresenham(p, x, y, 350 + (mapx - mapy - 1) * 32,
					300 - (p->info[i + p->lenx])
						+ (mapx + mapy + 1) * 16);
		}
		mapx = -1;
	}
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

	ft_putstr(map);
	p->info = get_map_info(map, p);

	int i = -1;
	while (++i < (p->len_map + 1))
	{
		ft_putnbr(p->info[i]);
		ft_putstr(" ");
	}

	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, W_LEN, W_HEI, "mlx test");
	p->img_ptr = mlx_new_image(p->mlx_ptr, W_LEN, W_HEI);
	p->img_data = mlx_get_data_addr(p->img_ptr,
		&p->bpp, &p->size_line, &p->endian);

	grid(p);

	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);

	mlx_key_hook(p->win_ptr, deal_key, p);
	mlx_loop(p->mlx_ptr);

	return (0);
}

