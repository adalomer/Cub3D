/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:27:42 by omadali           #+#    #+#             */
/*   Updated: 2025/08/07 02:27:51 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../headers/gc.h"

void	*gc_malloc(t_gc *gc, size_t size)
{
	void		*ptr;
	t_gc_node	*node;

	if (!gc || size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_gc_node));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->value.ptr = ptr;
	node->next = gc->allocations;
	gc->allocations = node;
	node->type = 1;
	return (ptr);
}

char	*gc_strdup(t_gc *gc, const char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	dup = gc_malloc(gc, len);
	if (dup)
		ft_memcpy(dup, s, len);
	return (dup);
}