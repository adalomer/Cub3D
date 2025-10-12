/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 02:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/12 04:39:35 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600

# define ESC_KEY 65307
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

# define MOVE_SPEED 0.0125
# define ROT_SPEED 0.0125
# define FOV (M_PI / 3)

#endif
