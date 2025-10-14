/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:39:38 by omadali           #+#    #+#             */
/*   Updated: 2025/10/14 16:11:06 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	main(int argc, char **argv)
{
	int		map_fd;
	t_info	*info;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Usage: ./Cub3d <map.cub>\n", 2);
		exit(1);
	}
	if (!is_valid_file(argv[1]))
	{
		ft_putstr_fd("Error: Invalid file\n", 2);
		exit(1);
	}
	map_fd = open_fd(argv[1]);
	if (map_fd == -1)
	{
		ft_putstr_fd("Error: Cannot open file\n", 2);
		exit(1);
	}
	info = parse_file(map_fd);
	close_fd(map_fd);
	if (!info)
	{
		ft_putstr_fd("Error: Failed to parse file\n", 2);
		exit(1);
	}
	cub_main(info);
	safe_exit(0);
	return (0);
}
