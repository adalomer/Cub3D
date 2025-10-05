/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/05 15:00:00 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libs/minilibx-linux/mlx.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

static void	put_pixel(t_info *info, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = info->img_data + (y * info->line_length + x * (info->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
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

void	draw_ceiling_and_floor(t_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(info, x, y, info->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(info, x, y, info->floor_color);
			x++;
		}
		y++;
	}
}

void	draw_vertical_line(t_info *info, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y <= end && y < SCREEN_HEIGHT)
	{
		if (y >= 0)
			put_pixel(info, x, y, color);
		y++;
	}
}
