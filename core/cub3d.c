/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:51:56 by omadali           #+#    #+#             */
/*   Updated: 2025/10/12 04:39:35 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libs/minilibx-linux/mlx.h"
#include <stdio.h>
int	is_valid_file(const char *filename)
{
	const char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strncmp(ext, ".cub", 5) != 0)
		return (0);
	return (1);
}

int	open_fd(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_putstr_fd("Error: Could not open file.\n", 2);
	return (fd);
}

void	close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	safe_exit(int code)
{
	exit(code);
}



static void	setup_hooks(t_info *info)
{
	mlx_hook(info->win, 17, 0, close_window, info);
	mlx_hook(info->win, 2, 1L << 0, key_press, info);
	mlx_hook(info->win, 3, 1L << 1, key_release, info);
	mlx_loop_hook(info->mlx, game_loop, info);
}

void	cub_main(t_info *info)
{
	info->mlx = mlx_init();
	if (!info->mlx)
	{
		ft_putstr_fd("Error: mlx_init() failed.\n", 2);
		safe_exit(1);
	}
	info->win = mlx_new_window(info->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "cub3D");
	if (!info->win)
	{
		ft_putstr_fd("Error: mlx_new_window() failed.\n", 2);
		safe_exit(1);
	}
	if (!load_textures(info))
		safe_exit(1);
	setup_hooks(info);
	mlx_loop(info->mlx);
}
