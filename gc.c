/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:39:34 by omadali           #+#    #+#             */
/*   Updated: 2025/08/07 00:43:01 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void *safe_malloc(size_t size)
{
	void *ptr;
	ptr = gc_malloc(size);
	if(!ptr)
	{
		perror("Memory allocation failed");
		gc_free_all();
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void *gc_malloc(size_t size)
{
	void *ptr;
	//linked list to keep track of allocated memory
}