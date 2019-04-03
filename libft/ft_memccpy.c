/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:47:55 by cseguier          #+#    #+#             */
/*   Updated: 2019/03/06 15:41:03 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, void const *src, int c, size_t n)
{
	size_t			i;
	unsigned char	x;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	s = (unsigned char*)src;
	d = (unsigned char*)dest;
	x = (unsigned char)c;
	while (i < n)
	{
		d[i] = s[i];
		if (d[i] == x)
			return (&d[i + 1]);
		i++;
	}
	return (NULL);
}
