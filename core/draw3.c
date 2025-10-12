/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 05:30:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/12 05:33:58 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libs/minilibx-linux/mlx.h"

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
