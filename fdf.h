/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 16:28:48 by cseguier          #+#    #+#             */
/*   Updated: 2019/04/19 16:19:57 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include "minilibx_macos/mlx.h"

# define W_LEN 1000
# define W_HEI 1000

typedef struct	linkedlist 
{
	int					tab;
	struct linkedlist	*next;
}				linkedlist;

typedef struct	s_param
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		h;
	int		i_max;
	int		i_min;
	int		dx;
	int		dy;
	int		x_i;
	int		y_i;
	int		cpt;
	int		incr;
	int		rx;
	int		ry;
	int		tx;
	int		ty;
	struct linkedlist	*first;
	int		*tab;

	int		lenx;
	int		leny;
	int		len_map;

	char	*img_data;

	int		bpp;
	int		size_line;
	int		e;

	void	*img_ptr;
	void	*mlx_ptr;
	void	*win_ptr;
}				t_param;

void			put_exit(char *msg);
void			parser(char *name, t_param *param, linkedlist **list);
int				*get_map_info(t_param *param);
void			bresenham(t_param *p);
void			grid(t_param *p, int i, int mapx, int mapy);
int				key_hook(int key, void *p);
int				expose_hook(t_param *p);
void 			newNode(int data, linkedlist **list);
int				getNode(int i, t_param *p);

#endif
