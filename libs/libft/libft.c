/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:21:40 by omadali           #+#    #+#             */
/*   Updated: 2025/08/07 02:35:07 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	a;
	char	*e;
	char	*d;

	if (!dest && !src)
		return (0);
	e = (char *)dest;
	d = (char *)src;
	a = 0;
	while (a < n)
	{
		e[a] = d[a];
		a++;
	}
	return (dest);
}