/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 02:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/18 21:31:42 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libs/minilibx-linux/mlx.h"

int	get_pixel_from_texture(t_texture_image *texture, int x, int y)
{
	char	*addr;
	int		byte_per_pixel;
	int		pixel;

	if (!texture || !texture->ptr || !texture->data_addr)
		return (0x808080);
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x808080);
	byte_per_pixel = texture->bits_per_pixel / 8;
	addr = texture->data_addr + texture->size_line * y + byte_per_pixel * x;
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
