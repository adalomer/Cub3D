/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 04:30:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/18 21:31:42 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

char	**convert_list_to_map(t_list *map_lines, int size)
{
	char	**map;
	int		i;
	t_list	*current;

	map = (char **)gc_malloc(sizeof(char *) * (size + 1));
	if (!map)
		safe_exit(1);
	current = map_lines;
	i = 0;
	while (current && i < size)
	{
		map[i] = gc_strdup((char *)current->content);
		if (!map[i])
			safe_exit(1);
		current = current->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	free_map_data(char **map)
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
