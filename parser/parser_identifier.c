/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_identifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 02:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/18 21:31:42 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include <stdio.h>

static int	process_north_south(char **parts, t_info *info)
{
	if (ft_strncmp(parts[0], "NO", 3) == 0 && !info->no_texture)
	{
		info->no_texture = gc_strtrim(parts[1], " \t\n\r");
		info->no = info->no_texture;
		printf("DEBUG: NO texture path = '%s'\n", info->no);
		return (info->no_texture != NULL);
	}
	else if (ft_strncmp(parts[0], "SO", 3) == 0 && !info->so_texture)
	{
		info->so_texture = gc_strtrim(parts[1], " \t\n\r");
		info->so = info->so_texture;
		printf("DEBUG: SO texture path = '%s'\n", info->so);
		return (info->so_texture != NULL);
	}
	return (0);
}

static int	process_west_east(char **parts, t_info *info)
{
	if (ft_strncmp(parts[0], "WE", 3) == 0 && !info->we_texture)
	{
		info->we_texture = gc_strtrim(parts[1], " \t\n\r");
		info->we = info->we_texture;
		printf("DEBUG: WE texture path = '%s'\n", info->we);
		return (info->we_texture != NULL);
	}
	else if (ft_strncmp(parts[0], "EA", 3) == 0 && !info->ea_texture)
	{
		info->ea_texture = gc_strtrim(parts[1], " \t\n\r");
		info->ea = info->ea_texture;
		printf("DEBUG: EA texture path = '%s'\n", info->ea);
		return (info->ea_texture != NULL);
	}
	return (0);
}

static int	process_texture(char **parts, t_info *info)
{
	int	result;

	result = process_north_south(parts, info);
	if (!result)
		result = process_west_east(parts, info);
	return (result);
}

static int	process_color(char **parts, t_info *info)
{
	if (ft_strncmp(parts[0], "F", 2) == 0 && info->floor_color == -1)
	{
		info->floor_color = parse_color(parts[1]);
		return (info->floor_color != -1);
	}
	else if (ft_strncmp(parts[0], "C", 2) == 0 && info->ceiling_color == -1)
	{
		info->ceiling_color = parse_color(parts[1]);
		return (info->ceiling_color != -1);
	}
	return (0);
}

int	process_identifier_line(char *line, t_info *info)
{
	char	**parts;
	char	*trimmed;
	int		is_valid;

	trimmed = gc_strtrim(line, " \t\n\r\v\f");
	if (!trimmed || trimmed[0] == '\0')
		safe_exit(1);
	parts = gc_split(trimmed, ' ');
	if (!parts || !parts[0] || !parts[1])
		safe_exit(1);
	is_valid = process_texture(parts, info);
	if (!is_valid)
		is_valid = process_color(parts, info);
	if (is_valid)
		info->identifiers_found++;
	return (is_valid);
}
