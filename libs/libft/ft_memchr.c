/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:44:16 by omadali           #+#    #+#             */
/*   Updated: 2025/10/17 19:30:16 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			a;
	unsigned char	*d;

	d = (unsigned char *)s;
	a = 0;
	c = (unsigned char)c;
	while (a < n)
	{
		if (d[a] == (unsigned char)c)
			return ((void *)&d[a]);
		a++;
	}
	return (0);
}
