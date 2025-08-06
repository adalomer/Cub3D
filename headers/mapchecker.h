/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapchecker.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:48:32 by omadali           #+#    #+#             */
/*   Updated: 2025/08/07 02:48:42 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPCHECKER_H
# define MAPCHECKER_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../headers/cub3d.h"

int		is_floor(char c);
int		is_valid_file(char *file);

#endif