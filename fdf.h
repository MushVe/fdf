/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 16:28:48 by cseguier          #+#    #+#             */
/*   Updated: 2019/04/03 18:42:40 by cseguier         ###   ########.fr       */
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

typedef struct	s_param
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;

	int dx;
	int dy;
	int x_i;
	int y_i;
	int cpt;
	int incr;

	int		lenx;
	int		leny;
	int		len_map;
	int		*info;

	char	*img_data;

	int		bpp;
	int		size_line;
	int		endian;

	void	*img_ptr;
	void	*mlx_ptr;
	void	*win_ptr;
}				t_param;

void	put_exit(char *msg);
char	*parser(char *name, t_param *param);
int		*get_map_info(char *map, t_param *param);

#endif
