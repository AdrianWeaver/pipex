/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_my_get_next_line.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:50:34 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/10 11:07:18 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOT_MY_GET_NEXT_LINE_H
# define NOT_MY_GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef GNL_FLUSH
#  define GNL_FLUSH -1
# endif

# ifndef GET_NEXT_LINE
#  define GET_NEXT_LINE

char	*get_next_line(int fd);

# endif
#endif
