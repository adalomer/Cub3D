/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 02:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/12 04:39:35 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libs/minilibx-linux/mlx.h"

static void	draw_ceiling(t_info *info)
{
	int				y;
	char			*line_start;
	int				x;
	unsigned int	*pixel;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		line_start = info->img_data + (y * info->line_length);
		pixel = (unsigned int *)line_start;
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			pixel[x] = info->ceiling_color;
			x++;
		}
		y++;
	}
}

static void	draw_floor(t_info *info)
{
	int				y;
	char			*line_start;
	int				x;
	unsigned int	*pixel;

	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		line_start = info->img_data + (y * info->line_length);
		pixel = (unsigned int *)line_start;
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			pixel[x] = info->floor_color;
			x++;
		}
		y++;
	}
}

void	draw_ceiling_and_floor(t_info *info)
{
	draw_ceiling(info);
	draw_floor(info);
}

void	draw_vertical_line(t_draw_params params)
{
	int		y;
	char	*dst;
	int		bytes_per_pixel;

	bytes_per_pixel = params.info->bits_per_pixel / 8;
	y = params.start;
	while (y <= params.end && y < SCREEN_HEIGHT)
	{
		if (y >= 0)
		{
			dst = params.info->img_data + (y * params.info->line_length
					+ params.x * bytes_per_pixel);
			*(unsigned int *)dst = params.color;
		}
		y++;
	}
}
