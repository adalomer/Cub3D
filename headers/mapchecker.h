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

typedef struct s_info	t_info;

int		validate_map(t_info *info);
int		is_floor(char c);

#endif