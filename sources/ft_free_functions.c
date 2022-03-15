/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:53:34 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/15 11:39:22 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include <stdio.h>
#include "libftprintf.h"
#include "not_my_libft.h"

int	ft_nuke_malloc(char **path, int i)
{
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	perror("");
	exit (12);
}

void	ft_free_path(char **path)
{
	int	i;

	i = 0;
	if (path == 0)
		return ;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	ft_free_cmd(char **cmd)
{
	int	i;

	i = 0;
	if (cmd == 0)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	ft_check_execve(char **path, char **cmd, int exe_read)
{
	if (exe_read == -1)
	{
		ft_free_path(path);
		perror("");
		ft_free_cmd(cmd);
		exit (127);
	}
}

void	ft_fork_fail(char **path)
{
	ft_free_path(path);
	perror("");
	exit (1);
}
