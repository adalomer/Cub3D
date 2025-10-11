/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:44:10 by omadali           #+#    #+#             */
/*   Updated: 2025/10/05 14:33:41 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

#include <stdlib.h>

char	*ft_get_slice(char *cake);
char	*ft_get_leftover(char *cake);
char	*ft_make_cake(int fd, char *cake);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr_gnl(char *str);
size_t	ft_strlen_gnl(char *s);

#endif