/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:14:59 by omadali           #+#    #+#             */
/*   Updated: 2025/08/23 23:33:45 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "mapchecker.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_info
{
	// Doku yolları
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;

	// Zemin ve tavan renkleri
	int		floor_color;
	int		ceiling_color;

	int		identifiers_found;

	// Harita
	char	**map;
	int		map_width;
	int		map_height;

	// Oyuncu başlangıç bilgileri
	double	player_x;
	double	player_y;
	char	player_dir;

	// MLX ile ilgili pointerlar
	void	*mlx;
	void	*win;

}	t_info;

// Function Prototypes
t_info	*parse_file(int fd);
t_info	*init_info(void);
int		is_valid_file(const char *filename);
int		open_fd(const char *filename);
void	close_fd(int fd);
void	cub_main(t_info *info);
void	safe_exit(int code);

// Parser utils
int		is_empty_line(const char *line);
void	free_split(char **split_array);
int		parse_color(const char *color_str);

#endif