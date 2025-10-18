/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:51:11 by omadali           #+#    #+#             */
/*   Updated: 2025/10/18 21:31:42 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libs/minilibx-linux/mlx.h"

static void	init_texture_params(t_draw_params params, int *tex_x,
		double *step_y, int wall_height)
{
	if (params.ray->texture && params.ray->texture->ptr)
	{
		*tex_x = (int)(params.ray->wall_x * params.ray->texture->width);
		*tex_x = (*tex_x < 0) ? 0 : *tex_x;
		*tex_x = (*tex_x >= params.ray->texture->width) ? 
				params.ray->texture->width - 1 : *tex_x;
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
		tex_y = (tex_y >= params.ray->texture->height) ? 
				params.ray->texture->height - 1 : tex_y;
		tex_y = (tex_y < 0) ? 0 : tex_y;
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
			put_pixel(params.info, params.x, y, 
				get_wall_pixel_color(params, tex_x, (int)tex_pos));
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
		gc_register_mlx_img(info->img);
	}
	draw_ceiling_and_floor(info);
	cast_rays(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
}
