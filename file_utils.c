/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 05:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/18 21:31:42 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

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
