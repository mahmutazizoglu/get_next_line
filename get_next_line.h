/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maazizog <maazizog@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 10:51:17 by maazizog          #+#    #+#             */
/*   Updated: 2026/06/22 15:51:34 by maazizog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*get_next_line(int fd);
char		*ft_find_newline(char *str);
char		*ft_save_remainder(char *saved);
int			ft_strlen(char const *str);
int			ft_line_len(char *saved);
char		*ft_strjoin(char const *s1, char const *s2);

#endif