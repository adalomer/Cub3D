/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/18 21:32:20 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/gc.h"
#include "../headers/cub3d.h"
#include <stdio.h>

t_gc	*get_gc(void)
{
	static t_gc	gc = {NULL};
	
	return (&gc);
}

void	*gc_malloc(size_t size)
{
	void		*ptr;
	t_gc_node	*new_node;
	t_gc		*gc;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	
	gc = get_gc();
	new_node->ptr = ptr;
	new_node->next = gc->head;
	gc->head = new_node;
	
	return (ptr);
}

void	gc_add_ptr(void *ptr)
{
	t_gc_node	*new_node;
	t_gc		*gc;

	if (!ptr)
		return ;
	
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
		return ;
	
	gc = get_gc();
	new_node->ptr = ptr;
	new_node->next = gc->head;
	gc->head = new_node;
}

void	gc_remove_ptr(void *ptr)
{
	t_gc		*gc;
	t_gc_node	*current;
	t_gc_node	*prev;

	if (!ptr)
		return ;
	
	gc = get_gc();
	current = gc->head;
	prev = NULL;
	
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				gc->head = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	gc_free_all(void)
{
	t_gc		*gc;
	t_gc_node	*current;
	t_gc_node	*next;

	gc = get_gc();
	current = gc->head;
	
	while (current)
	{
		next = current->next;
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	
	gc->head = NULL;
}

void	safe_exit(int code)
{
	gc_cleanup_mlx();
	gc_free_all();
	exit(code);
}

typedef struct s_mlx_cleanup
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*texture_north;
	void	*texture_south;
	void	*texture_east;
	void	*texture_west;
}	t_mlx_cleanup;

static t_mlx_cleanup	g_mlx_data = {0};

void	gc_register_mlx(void *mlx, void *win)
{
	g_mlx_data.mlx = mlx;
	g_mlx_data.win = win;
}

void	gc_register_mlx_img(void *img)
{
	g_mlx_data.img = img;
}

void	gc_register_mlx_textures(void *north, void *south, void *east, void *west)
{
	g_mlx_data.texture_north = north;
	g_mlx_data.texture_south = south;
	g_mlx_data.texture_east = east;
	g_mlx_data.texture_west = west;
}

void	gc_cleanup_mlx(void)
{
	extern int	mlx_destroy_image(void *mlx_ptr, void *img_ptr);
	extern int	mlx_destroy_window(void *mlx_ptr, void *win_ptr);
	extern int	mlx_destroy_display(void *mlx_ptr);

	if (g_mlx_data.mlx)
	{
		if (g_mlx_data.texture_north)
			mlx_destroy_image(g_mlx_data.mlx, g_mlx_data.texture_north);
		if (g_mlx_data.texture_south)
			mlx_destroy_image(g_mlx_data.mlx, g_mlx_data.texture_south);
		if (g_mlx_data.texture_east)
			mlx_destroy_image(g_mlx_data.mlx, g_mlx_data.texture_east);
		if (g_mlx_data.texture_west)
			mlx_destroy_image(g_mlx_data.mlx, g_mlx_data.texture_west);
		if (g_mlx_data.img)
			mlx_destroy_image(g_mlx_data.mlx, g_mlx_data.img);
		if (g_mlx_data.win)
			mlx_destroy_window(g_mlx_data.mlx, g_mlx_data.win);
		mlx_destroy_display(g_mlx_data.mlx);
		free(g_mlx_data.mlx);
	}
	g_mlx_data = (t_mlx_cleanup){0};
}
