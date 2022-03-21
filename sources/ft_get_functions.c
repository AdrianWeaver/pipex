/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:03:33 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/15 14:03:57 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include <stdio.h>
#include "libftprintf.h"
#include "not_my_libft.h"

void	ft_check_params(int argc)
{
	int	save_stdout;

	save_stdout = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (argc < 5)
	{
		ft_printf(RED"Insufficient amount of parameters, provide 4\n"NOCOLOUR);
		exit(1);
	}
	if (argc > 5)
	{
		ft_printf(RED"Too many parameters given please provide 4\n"NOCOLOUR);
		exit(1);
	}
	dup2(save_stdout, STDOUT_FILENO);
}

char	**ft_cat_path(char *envp)
{
	int		i;
	char	**path;
	char	*tmp;
	size_t	path_len;

	i = 0;
	path = ft_split(ft_strchr(envp, '=') + 1, ':');
	while (path[i])
	{
		if (path[i] && path[i][0] != 0)
		{
			path_len = ft_strlen(path[i]);
			tmp = malloc(sizeof(*tmp) * (path_len) + 103);
			if (tmp == 0)
				ft_nuke_malloc(path, i);
			tmp = ft_strcpy(tmp, path[i]);
			tmp[path_len] = '/';
			tmp[path_len + 1] = 0;
			free(path[i]);
			path[i] = tmp;
		}
		i++;
	}
	return (path);
}

char	**ft_get_path(char **envp, char **argv)
{
	if (envp == 0 || *envp == 0)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		ft_printf("%s: %s: No such file or directory\n", argv[2], argv[3]);
		exit (127);
	}
	while (*envp != 0)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_cat_path(*envp));
		envp++;
	}
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("%s: %s: No such file or directory\n", argv[2], argv[3]);
	exit (127);
}

char	**ft_get_cmd(char *argv)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	return (cmd);
}
