/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:03:33 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/15 09:04:48 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include <stdio.h>
#include "libftprintf.h"
#include "not_my_libft.h"

void	ft_check_params(int argc)
{
	if (argc < 5)
	{
		ft_printf(RED"Insufficient amount of parameters, provide 4\n"NOCOLOUR);
		exit(0);
	}
	if (argc > 5)
	{
		ft_printf(RED"Too many parameters given please provide 4\n"NOCOLOUR);
		exit(0);
	}
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

char	**ft_get_path(char **envp)
{
	if (envp == 0 || *envp == 0)
	{
		ft_printf(RED"It seems like the env is missing, are you for real?\n"
			NOCOLOUR);
		exit (0);
	}
	while (*envp != 0)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_cat_path(*envp));
		envp++;
	}
	ft_printf(RED"It seems like the PATH is missing from the env, but why?!\n"
		" are you trying to sabotage this?!\n"NOCOLOUR);
	exit (0);
}

char	**ft_get_cmd(char *argv)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	return (cmd);
}
