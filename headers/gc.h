/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/18 21:31:42 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node	*head;
}	t_gc;

// Garbage Collector Functions
void	*gc_malloc(size_t size);
void	gc_free_all(void);
void	gc_add_ptr(void *ptr);
void	gc_remove_ptr(void *ptr);
t_gc	*get_gc(void);

// MLX Cleanup Functions
void	gc_register_mlx(void *mlx, void *win);
void	gc_register_mlx_img(void *img);
void	gc_register_mlx_textures(void *north, void *south, void *east, void *west);
void	gc_cleanup_mlx(void);

// Safe exit function
void	safe_exit(int code);

// Wrapper functions for common allocations
char	*gc_strdup(const char *s1);
char	**gc_split(char const *s, char c);
char	*gc_strtrim(char const *s1, char const *set);

#endif
