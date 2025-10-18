/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:39:45 by omadali           #+#    #+#             */
/*   Updated: 2025/10/18 21:31:42 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../headers/get_next_line.h"
#include "../headers/libft.h"
#include "../headers/mapchecker.h"
#include <stdio.h>

static int	parse_identifiers(int fd, t_info *info);
static int	parse_map(int fd, t_info *info);
int			process_identifier_line(char *line, t_info *info);
char		**convert_list_to_map(t_list *map_lines, int size);
void		free_map_data(char **map);

t_info	*parse_file(int fd)
{
	t_info	*info;

	if (fd < 0)
	{
		ft_putstr_fd("Error: Invalid file descriptor\n", 2);
		safe_exit(1);
	}
	info = init_info();
	if (!info)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		safe_exit(1);
	}
	if (!parse_identifiers(fd, info))
	{
		ft_putstr_fd("Error: Invalid or incomplete identifiers.\n", 2);
		safe_exit(1);
	}
	if (!parse_map(fd, info))
	{
		ft_putstr_fd("Error: Invalid map.\n", 2);
		safe_exit(1);
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
			break ;
		gc_add_ptr(line);
		if (!is_empty_line(line))
		{
			if (!process_identifier_line(line, info))
				safe_exit(1);
		}
	}
	if (info->identifiers_found != 6)
		safe_exit(1);
	return (1);
}

static int	process_map_line(char *line, t_list **map_lines,
		int *map_started, int *empty_count)
{
	char	*trimmed;

	trimmed = gc_strtrim(line, " \t\n\r\v\f");
	if (trimmed && trimmed[0] != '\0')
	{
		if (*empty_count > 0 && *map_started)
			ft_putstr_fd("Warning: Empty lines in map ignored\n", 2);
		*map_started = 1;
		*empty_count = 0;
		ft_lstadd_back(map_lines, ft_lstnew(trimmed));
		return (1);
	}
	else
	{
		if (*map_started)
			(*empty_count)++;
		return (0);
	}
}

static int	validate_and_convert_map(t_info *info, t_list *map_lines)
{
	if (!map_lines)
	{
		ft_putstr_fd("Error: No map found\n", 2);
		return (0);
	}
	if (!info)
	{
		ft_putstr_fd("Error: Info structure is NULL\n", 2);
		ft_lstclear(&map_lines, free);
		return (0);
	}
	info->map_height = ft_lstsize(map_lines);
	if (info->map_height == 0)
	{
		ft_putstr_fd("Error: Empty map\n", 2);
		ft_lstclear(&map_lines, free);
		return (0);
	}
	info->map = convert_list_to_map(map_lines, info->map_height);
	ft_lstclear(&map_lines, free);
	if (!info->map)
	{
		ft_putstr_fd("Error: Map conversion failed\n", 2);
		return (0);
	}
	if (!validate_map(info))
	{
		ft_putstr_fd("Error: Map validation failed\n", 2);
		return (0);
	}
	return (1);
}

static int	parse_map(int fd, t_info *info)
{
	char	*line;
	t_list	*map_lines;
	int		map_started;
	int		empty_count;

	map_lines = NULL;
	map_started = 0;
	empty_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		gc_add_ptr(line);
		process_map_line(line, &map_lines, &map_started, &empty_count);
		line = get_next_line(fd);
	}
	return (validate_and_convert_map(info, map_lines));
}
