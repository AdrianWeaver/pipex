/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:52:50 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/14 16:57:55 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_pipex_data
{
	char	**path;
	char	**cmd1;
	char	**cmd2;
}				t_pipex_data;

# define READ_END 0
# define WRITE_END 1

# ifndef FT_NUKE_MALLOC
#  define FT_NUKE_MALLOC

int		ft_nuke_malloc(char **path, int i);

# endif

# ifndef FT_FREE_PATH
#  define FT_FREE_PATH

void	ft_free_path(char **path);

# endif

# ifndef FT_FREE_CMD
#  define FT_FREE_CMD

void	ft_free_cmd(char **cmd);

# endif

# ifndef FT_CHECK_EXECVE
#  define FT_CHECK_EXECVE

void	ft_check_execve(char **path, char **cmd, int exe_read);

# endif

# ifndef FT_FORK_FAIL
#  define FT_FORK_FAIL

void	ft_fork_fail(char **path);

# endif

#endif
