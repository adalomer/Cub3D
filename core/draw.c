/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:51:11 by omadali           #+#    #+#             */
/*   Updated: 2025/10/06 19:19:07 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libs/minilibx-linux/mlx.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/* Sets a pixel at coordinates (x,y) with given color in the image buffer */
/* NOTE: This function is kept for compatibility but not used in main rendering */
void	put_pixel(t_info *info, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = info->img_data + (y * info->line_length + x * (info->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

/* Extracts pixel color from texture at given coordinates */
int	get_pixel_from_texture(t_texture_image *texture, int x, int y)
{
	char	*addr;
	int		pixel;
	int		byte_per_pixel;

	if (!texture || !texture->ptr || !texture->data_addr)
		return (0x808080);
	
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x808080);
	
	byte_per_pixel = texture->bits_per_pixel / 8;
	addr = texture->data_addr + texture->size_line * y + byte_per_pixel * x;
	
	pixel = 0;
	if (byte_per_pixel == 4)
		pixel = *(int*)addr;
	else if (byte_per_pixel == 3)
	{
		pixel = (addr[2] << 16) | (addr[1] << 8) | addr[0];
	}
	else if (byte_per_pixel == 2)
	{
		pixel = *(short*)addr;
	}
	else
		pixel = *addr;
	
	return (pixel);
}

/* Draws a vertical textured line from start to end at column x */
void	draw_textured_line(t_info *info, int x, int start, int end, t_ray_result *ray)
{
	int		y;
	int		color;
	int		wall_height;
	int		tex_x, tex_y;
	double	step_y;
	double	tex_pos;
	char	*dst;
	
	wall_height = end - start;
	if (wall_height <= 0)
		return;
	
	if (ray->texture && ray->texture->ptr)
	{
		// Calculate texture X coordinate (which column of the texture to use)
		tex_x = (int)(ray->wall_x * ray->texture->width);
		if (tex_x < 0) tex_x = 0;
		if (tex_x >= ray->texture->width) tex_x = ray->texture->width - 1;
		
		// Calculate step: how much texture Y changes per screen pixel
		step_y = (double)ray->texture->height / wall_height;
		
		// Start at the top of the wall texture
		tex_pos = 0;
	}
	else
	{
		tex_x = 0;
		step_y = 1.0;
		tex_pos = 0;
	}
	
	y = start;
	while (y <= end && y < SCREEN_HEIGHT)
	{
		if (y >= 0)
		{
			if (ray->texture && ray->texture->ptr)
			{
				tex_y = (int)tex_pos;
				if (tex_y >= ray->texture->height) tex_y = ray->texture->height - 1;
				if (tex_y < 0) tex_y = 0;
				
				color = get_pixel_from_texture(ray->texture, tex_x, tex_y);
			}
			else
			{
				if (ray->wall_direction == 0)
					color = 0x96CEB4;
				else if (ray->wall_direction == 1)
					color = 0x45B7D1;
				else if (ray->wall_direction == 2)
					color = 0xFF6B6B;
				else
					color = 0x4ECDC4;
			}
			// Direct image buffer write instead of put_pixel function call
			dst = info->img_data + (y * info->line_length + x * (info->bits_per_pixel / 8));
			*(unsigned int*)dst = color;
		}
		tex_pos += step_y;
		y++;
	}
}

/* Creates image buffer, renders frame, and displays it */
void	draw_frame(t_info *info)
{
	if (!info->img)
	{
		info->img = mlx_new_image(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
		info->img_data = mlx_get_data_addr(info->img, &info->bits_per_pixel, 
			&info->line_length, &info->endian);
	}
	draw_ceiling_and_floor(info);
	cast_rays(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
}

/* Fills the upper half with ceiling color and lower half with floor color */
void	draw_ceiling_and_floor(t_info *info)
{
	int		x;
	int		y;
	char	*dst;
	int		bytes_per_pixel;

	bytes_per_pixel = info->bits_per_pixel / 8;
	
	// Draw ceiling
	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			dst = info->img_data + (y * info->line_length + x * bytes_per_pixel);
			*(unsigned int*)dst = info->ceiling_color;
			x++;
		}
		y++;
	}
	
	// Draw floor
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			dst = info->img_data + (y * info->line_length + x * bytes_per_pixel);
			*(unsigned int*)dst = info->floor_color;
			x++;
		}
		y++;
	}
}

/* Draws a solid color vertical line from start to end at column x */
void	draw_vertical_line(t_info *info, int x, int start, int end, int color)
{
	int		y;
	char	*dst;
	int		bytes_per_pixel;

	bytes_per_pixel = info->bits_per_pixel / 8;
	y = start;
	while (y <= end && y < SCREEN_HEIGHT)
	{
		if (y >= 0)
		{
			dst = info->img_data + (y * info->line_length + x * bytes_per_pixel);
			*(unsigned int*)dst = color;
		}
		y++;
	}
}
