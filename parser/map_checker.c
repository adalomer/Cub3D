/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:46:51 by omadali           #+#    #+#             */
/*   Updated: 2025/08/07 02:49:07 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/mapchecker.h"

int	is_floor(char c)
{
	return (c == '0' || c == 'S' || c == 'N' || c == 'E' || c == 'W');
}
int	is_valid_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}