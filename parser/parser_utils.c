/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/06 19:19:07 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	is_empty_line(const char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r' && line[i] != '\v' && line[i] != '\f')
			return (0);
		i++;
	}
	return (1);
}

void	free_split(char **split_array)
{
	int	i;

	if (!split_array)
		return;
	i = 0;
	while (split_array[i])
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}

int	parse_color(const char *color_str)
{
	char	**rgb_parts;
	char	*trimmed;
	int		r;
	int		g;
	int		b;
	int		color;

	trimmed = ft_strtrim(color_str, " \t\n\r\v\f");
	if (!trimmed)
		return (-1);
	
	rgb_parts = ft_split(trimmed, ',');
	free(trimmed);
	
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2])
	{
		free_split(rgb_parts);
		return (-1);
	}
	
	r = ft_atoi(ft_strtrim(rgb_parts[0], " \t"));
	g = ft_atoi(ft_strtrim(rgb_parts[1], " \t"));
	b = ft_atoi(ft_strtrim(rgb_parts[2], " \t"));
	
	free_split(rgb_parts);
	
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	
	color = (r << 16) | (g << 8) | b;
	return (color);
}
