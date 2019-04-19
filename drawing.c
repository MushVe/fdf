/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:50:10 by cseguier          #+#    #+#             */
/*   Updated: 2019/04/09 15:49:24 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** +++++++[ Gradiant ]++++++++
** FFDE00	jaune :)	FFDE00
** E6DB1C				FFC90B
** CED838				FFB416
** B6D555				FFA021
** 9DD271				FF8B2C
** 85CF8D				FF7637
** 6DCCAA				FF6242
** 54C9C6				FF4D4D
** 3CC6E2				FF3858
** 24C3FF	bleu/rose	FF2464
** +++++++++++++++++++++++++++
*/

void	put_data(t_param *p, int incr)
{
	p->img_data[incr] = 0x00;
	p->img_data[incr + 1] = 0xDE;
	p->img_data[incr + 2] = 0xFF;
	p->img_data[incr + 3] = 0x00;
}

void	bresx(t_param *p, int i, int x, int y)
{
	p->cpt = p->dx / 2;
	while (++i < p->dx)
	{
		x += p->x_i;
		p->cpt += p->dy;
		if (p->cpt >= p->dx)
		{
			p->cpt -= p->dx;
			y += p->y_i;
		}
		if (x <= W_LEN - 1 && y <= W_HEI - 1 && x >= 0 && y >= 0)
			put_data(p, ((y * W_HEI) + x) * 4);
	}
}

void	bresy(t_param *p, int i, int x, int y)
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
			put_data(p, ((y * W_HEI) + x) * 4);
	}
}

void	bresenham(t_param *p)
{
	int x;
	int y;

	x = p->x1;
	y = p->y1;
	p->dx = p->x2 - p->x1;
	p->dy = p->y2 - p->y1;
	p->x_i = (p->dx > 0) ? 1 : -1;
	p->y_i = (p->dy > 0) ? 1 : -1;
	p->dx = abs(p->dx);
	p->dy = abs(p->dy);
	if (p->dx > p->dy)
		bresx(p, -1, x, y);
	else
		bresy(p, -1, x, y);
}

void	grid(t_param *p, int i, int mapx, int mapy)
{
	while ((mapx = -1) && ++mapy < p->leny)
	{
		while (++mapx < p->lenx)
		{
			++i;
			p->x1 = p->tx + (mapx - mapy) * p->rx;
			p->y1 = p->ty - (get_node(i, p) * p->h) + (mapx + mapy) * p->ry;
			if (p->x1 <= W_LEN && p->x1 >= 0 && p->y1 <= W_HEI && p->y1 >= 0)
				put_data(p, ((p->y1 * W_HEI) + p->x1) * 4);
			if (mapx < p->lenx - 1)
			{
				p->x2 = p->tx + (mapx - mapy + 1) * p->rx;
				p->y2 = p->ty - (get_node(i + 1, p) * p->h)
					+ (mapx + mapy + 1) * p->ry;
				bresenham(p);
			}
			if (mapy < p->leny - 1)
			{
				p->x2 = p->tx + (mapx - mapy - 1) * p->rx;
				p->y2 = p->ty - (get_node(i + p->lenx, p) * p->h)
					+ (mapx + mapy + 1) * p->ry;
				bresenham(p);
			}
		}
	}
}
