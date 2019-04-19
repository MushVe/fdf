/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:50:48 by cseguier          #+#    #+#             */
/*   Updated: 2019/04/11 18:06:40 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		expose_hook(t_param *p)
{
	ft_bzero(p->img_data, W_LEN * W_HEI * p->bpp / 8);
	grid(p, -1, -1, -1);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	return (0);
}

void	slide_2(t_param *p, int key)
{
	if (key == 87)
	{
		p->rx = 32;
		p->ry = 16;
	}
	if (key == 89)
	{
		p->rx -= 2;
		p->ry -= 1;
	}
	if (key == 83)
	{
		p->rx += 2;
		p->ry += 1;
	}
	expose_hook(p);
}

void	slide(t_param *p, int key)
{
	if (key == 123)
		p->tx -= 10;
	if (key == 124)
		p->tx += 10;
	if (key == 125)
		p->ty += 10;
	if (key == 126)
		p->ty -= 10;
	if (key == 78)
		p->h -= 1;
	if (key == 69)
		p->h += 1;
	if (key == 91)
		p->ry += 1;
	if (key == 84)
		p->ry -= 1;
	if (key == 88)
		p->rx += 1;
	if (key == 86)
		p->rx -= 1;
	slide_2(p, key);
}

int		key_hook(int key, void *p)
{
	if (key == 53)
		put_exit("exit ./fdf");
	slide(p, key);
	return (0);
}
