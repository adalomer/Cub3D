/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:51:11 by omadali           #+#    #+#             */
/*   Updated: 2025/10/12 04:39:35 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libs/minilibx-linux/mlx.h"

void	put_pixel(t_info *info, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = info->img_data + (y * info->line_length + x * (info->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

static int	get_pixel_value(char *addr, int byte_per_pixel)
{
	int	pixel;

	if (byte_per_pixel == 4)
		pixel = *(int *)addr;
	else if (byte_per_pixel == 3)
		pixel = (addr[2] << 16) | (addr[1] << 8) | addr[0];
	else if (byte_per_pixel == 2)
		pixel = *(short *)addr;
	else
		pixel = *addr;
	return (pixel);
}

int	get_pixel_from_texture(t_texture_image *texture, int x, int y)
{
	char	*addr;
	int		byte_per_pixel;

	if (!texture || !texture->ptr || !texture->data_addr)
		return (0x808080);
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x808080);
	byte_per_pixel = texture->bits_per_pixel / 8;
	addr = texture->data_addr + texture->size_line * y + byte_per_pixel * x;
	return (get_pixel_value(addr, byte_per_pixel));
}

static void	init_texture_params(t_draw_params params, int *tex_x,
		double *step_y, int wall_height)
{
	if (params.ray->texture && params.ray->texture->ptr)
	{
		*tex_x = (int)(params.ray->wall_x * params.ray->texture->width);
		if (*tex_x < 0)
			*tex_x = 0;
		if (*tex_x >= params.ray->texture->width)
			*tex_x = params.ray->texture->width - 1;
		*step_y = (double)params.ray->texture->height / wall_height;
	}
	else
	{
		*tex_x = 0;
		*step_y = 1.0;
	}
}

static int	get_wall_fallback_color(int wall_direction)
{
	if (wall_direction == 0)
		return (0x96CEB4);
	else if (wall_direction == 1)
		return (0x45B7D1);
	else if (wall_direction == 2)
		return (0xFF6B6B);
	else
		return (0x4ECDC4);
}

static int	get_wall_pixel_color(t_draw_params params, int tex_x, int tex_y)
{
	int	color;

	if (params.ray->texture && params.ray->texture->ptr)
	{
		if (tex_y >= params.ray->texture->height)
			tex_y = params.ray->texture->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		color = get_pixel_from_texture(params.ray->texture, tex_x, tex_y);
	}
	else
		color = get_wall_fallback_color(params.ray->wall_direction);
	return (color);
}

void	draw_textured_line(t_draw_params params)
{
	int		y;
	int		tex_x;
	double	step_y;
	double	tex_pos;
	char	*dst;
	int		wall_height;

	wall_height = params.end - params.start;
	if (wall_height <= 0)
		return ;
	init_texture_params(params, &tex_x, &step_y, wall_height);
	tex_pos = 0;
	y = params.start - 1;
	while (++y <= params.end && y < SCREEN_HEIGHT)
	{
		if (y >= 0)
		{
			dst = params.info->img_data + (y * params.info->line_length
					+ params.x * (params.info->bits_per_pixel / 8));
			*(unsigned int *)dst = get_wall_pixel_color(params,
					tex_x, (int)tex_pos);
		}
		tex_pos += step_y;
	}
}

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
