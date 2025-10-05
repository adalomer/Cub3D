/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:14:59 by omadali           #+#    #+#             */
/*   Updated: 2025/10/05 14:33:45 by omadali          ###   ########.fr       */
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

// Texture and image structures
typedef struct s_texture_image
{
	void	*ptr;
	char	*data_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_texture_image;

typedef struct s_textures
{
	t_texture_image	north;
	t_texture_image	south;
	t_texture_image	east;
	t_texture_image	west;
}	t_textures;

// Ray result structure for texture mapping
typedef struct s_ray_result
{
	double	distance;
	double	wall_x;
	int		wall_direction; // 0=north, 1=south, 2=east, 3=west
	int		hit_side; // 0=vertical, 1=horizontal
	t_texture_image	*texture;
}	t_ray_result;

typedef struct s_info
{
	// Doku yolları
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;

	// Texture images
	void	*no_img;
	void	*so_img;
	void	*we_img;
	void	*ea_img;
	
	// New texture system
	t_textures	textures;
	
	// Old texture pointers (deprecated)
	void	*texture_north;
	void	*texture_south;
	void	*texture_east;
	void	*texture_west;
	
	// Texture path aliases
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	
	int		tex_width;
	int		tex_height;

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
	double	player_angle;

	// MLX ile ilgili pointerlar
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

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

// Game functions
int		close_window(t_info *info);
int		key_press(int keycode, t_info *info);
int		game_loop(t_info *info);

// Movement functions
void	move_forward(t_info *info);
void	move_backward(t_info *info);
void	move_left(t_info *info);
void	move_right(t_info *info);
void	rotate_left(t_info *info);
void	rotate_right(t_info *info);
double	get_player_angle(t_info *info);
int		is_valid_position(t_info *info, double x, double y);

// Raycasting functions
void	cast_rays(t_info *info);
double	cast_single_ray(t_info *info, double angle);
t_ray_result	cast_single_ray_detailed(t_info *info, double angle);
int		get_wall_color(t_info *info, double angle);
void	draw_textured_line(t_info *info, int x, int start, int end, t_ray_result *ray);
int		get_pixel_from_texture(t_texture_image *texture, int x, int y);

// Drawing functions
void	draw_frame(t_info *info);
void	draw_ceiling_and_floor(t_info *info);
void	draw_vertical_line(t_info *info, int x, int start, int end, int color);
void	put_pixel(t_info *info, int x, int y, int color);

#endif