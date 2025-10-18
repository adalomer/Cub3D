/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:44:10 by omadali           #+#    #+#             */
/*   Updated: 2025/10/18 20:03:06 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# define BUFFER_SIZE 1

char	*ft_get_slice(char *cake);
char	*ft_get_leftover(char *cake);
char	*ft_make_cake(int fd, char *cake);
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strchr_gnl(char *str);
size_t	ft_strlen_gnl(char *s);

#endif
