/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:39:34 by omadali           #+#    #+#             */
/*   Updated: 2025/08/07 02:38:32 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../headers/gc.h"
#include "../headers/libft.h"

t_gc	*gc_init(void)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	if (gc)
		gc->allocations = NULL;
	return (gc);
}

t_gc	*get_set_gc(t_gc *new_gc)
{
	static t_gc	*static_gc = NULL;

	if (new_gc != NULL)
		static_gc = new_gc;
	return (static_gc);
}

void	gc_destroy(t_gc *gc, int flag)
{
	if (!gc)
		return ;
	gc_free_all(gc);
	free(gc);
}

void	gc_free_all(t_gc *gc)
{
	t_gc_node	*tmp;

	if (!gc)
		return ;
	while (gc->allocations)
	{
		tmp = gc->allocations;
		gc->allocations = tmp->next;
		free(tmp->value.ptr);
		free(tmp);
	}
}
