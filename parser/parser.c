/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:39:45 by omadali           #+#    #+#             */
/*   Updated: 2025/10/06 19:19:07 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../headers/get_next_line.h"
#include "../headers/libft.h"
#include "../headers/mapchecker.h"
#include <stdio.h>

static int	parse_identifiers(int fd, t_info *info);
static int	parse_map(int fd, t_info *info);
static int	process_identifier_line(char *line, t_info *info);
static char	**convert_list_to_map(t_list *map_lines, int size);
static void	free_map_data(char **map);

t_info	*parse_file(int fd)
{
	t_info	*info;

	info = init_info();
	if (!info)
		return (NULL);
	if (!parse_identifiers(fd, info))
	{
		ft_putstr_fd("Error: Invalid or incomplete identifiers.\n", 2);
		return (NULL);
	}
	if (!parse_map(fd, info))
	{
		free_map_data(info->map);
		ft_putstr_fd("Error: Invalid map.\n", 2);
		return (NULL);
	}
	return (info);
}

static int	parse_identifiers(int fd, t_info *info)
{
	char	*line;

	while (info->identifiers_found < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (!is_empty_line(line))
		{
			if (!process_identifier_line(line, info))
			{
				free(line);
				return (0);
			}
		}
		free(line);
	}
	if (info->identifiers_found != 6)
		return (0);
	return (1);
}

static int	process_identifier_line(char *line, t_info *info)
{
	char	**parts;
	char	*trimmed;
	int		is_valid;

	// Trim and split by whitespace (space or tab)
	trimmed = ft_strtrim(line, " \t\n\r\v\f");
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		return (0);
	}
	
	parts = ft_split(trimmed, ' ');
	free(trimmed);
	
	if (!parts || !parts[0] || !parts[1])
	{
		free_split(parts);
		return (0);
	}
	
	is_valid = 0;
	if (ft_strncmp(parts[0], "NO", 3) == 0 && !info->no_texture)
	{
		info->no_texture = ft_strtrim(parts[1], " \t\n\r");
		info->no = info->no_texture;
		printf("DEBUG: NO texture path = '%s'\n", info->no);
		is_valid = (info->no_texture != NULL);
	}
	else if (ft_strncmp(parts[0], "SO", 3) == 0 && !info->so_texture)
	{
		info->so_texture = ft_strtrim(parts[1], " \t\n\r");
		info->so = info->so_texture;
		printf("DEBUG: SO texture path = '%s'\n", info->so);
		is_valid = (info->so_texture != NULL);
	}
	else if (ft_strncmp(parts[0], "WE", 3) == 0 && !info->we_texture)
	{
		info->we_texture = ft_strtrim(parts[1], " \t\n\r");
		info->we = info->we_texture;
		printf("DEBUG: WE texture path = '%s'\n", info->we);
		is_valid = (info->we_texture != NULL);
	}
	else if (ft_strncmp(parts[0], "EA", 3) == 0 && !info->ea_texture)
	{
		info->ea_texture = ft_strtrim(parts[1], " \t\n\r");
		info->ea = info->ea_texture;
		printf("DEBUG: EA texture path = '%s'\n", info->ea);
		is_valid = (info->ea_texture != NULL);
	}
	else if (ft_strncmp(parts[0], "F", 2) == 0 && info->floor_color == -1)
	{
		info->floor_color = parse_color(parts[1]);
		is_valid = (info->floor_color != -1);
	}
	else if (ft_strncmp(parts[0], "C", 2) == 0 && info->ceiling_color == -1)
	{
		info->ceiling_color = parse_color(parts[1]);
		is_valid = (info->ceiling_color != -1);
	}
	free_split(parts);
	if (is_valid)
		info->identifiers_found++;
	return (is_valid);
}

static int	parse_map(int fd, t_info *info)
{
	char	*line;
	char	*trimmed;
	t_list	*map_lines;
	int		map_started;
	int		empty_count;

	map_lines = NULL;
	map_started = 0;
	empty_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		trimmed = ft_strtrim(line, " \t\n\r\v\f");
		if (trimmed && trimmed[0] != '\0')
		{
			if (empty_count > 0 && map_started)
			{
				// Allow empty lines in map but warn
				ft_putstr_fd("Warning: Empty lines in map ignored\n", 2);
			}
			map_started = 1;
			empty_count = 0;
			ft_lstadd_back(&map_lines, ft_lstnew(trimmed));
		}
		else
		{
			if (map_started)
				empty_count++;
			free(trimmed);
		}
		free(line);
	}
	if (!map_lines)
		return (ft_putstr_fd("Error: No map found\n", 2), 0);
	info->map_height = ft_lstsize(map_lines);
	info->map = convert_list_to_map(map_lines, info->map_height);
	ft_lstclear(&map_lines, free);
	if (!info->map || !validate_map(info))
		return (0);
	return (1);
}

static char	**convert_list_to_map(t_list *map_lines, int size)
{
	char	**map;
	int		i;
	t_list	*current;

	map = (char **)malloc(sizeof(char *) * (size + 1));
	if (!map)
		return (NULL);
	current = map_lines;
	i = 0;
	while (current && i < size)
	{
		map[i] = ft_strdup((char *)current->content);
		if (!map[i])
		{
			while (i > 0)
				free(map[--i]);
			free(map);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

static void	free_map_data(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

