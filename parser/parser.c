/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:39:45 by omadali           #+#    #+#             */
/*   Updated: 2025/10/12 04:39:35 by omadali          ###   ########.fr       */
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


static int	process_map_line(char *line, t_list **map_lines,
		int *map_started, int *empty_count)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n\r\v\f");
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
		free(trimmed);
		return (0);
	}
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
	while ((line = get_next_line(fd)) != NULL)
	{
		process_map_line(line, &map_lines, &map_started, &empty_count);
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


