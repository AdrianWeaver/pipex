/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:19:28 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/10 16:45:19 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include <stdio.h>
#include "libftprintf.h"
#include "not_my_libft.h"

void	ft_check_params(int argc)
{
	//if (argc < 5)
	//{
		//ft_printf(RED"Insufficient amount of parameters, provide 4\n"NOCOLOUR);
		//exit(0);
	//}
	if (argc > 5)
	{
		ft_printf(RED"Too many parameters given please provide 4\n"NOCOLOUR);
		exit(0);
	}
}

char	**ft_get_path(char **envp)
{
	if (envp == 0 || *envp == 0)
	{
		ft_printf(RED"It seems like the env is missing, are you for real?\n");
		exit (0);
	}
	while (*envp != 0)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp, ':'));
		envp++;
	}
	ft_printf(RED"It seems like the PATH is missing from the env, but why?!\n"
		" are you trying to sabotage this?!\n"NOCOLOUR);
	exit (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		exe_read;
	char	**path;
	int		pid;
	int		w_status;
	char	**cmd;

	exe_read = -1;
	ft_check_params(argc);
	path = ft_get_path(envp);
	//while (*path)
	//{
		//ft_printf("%s\n", *path);
		//path++;
	//}
	pid = fork();
	if (pid == -1)
		//make an error return maybe using perror ?!
		return (-1);
	wait(&w_status);
	cmd = malloc(sizeof(*cmd) * (argc + 1));
	cmd[0] = malloc(sizeof(**cmd) * ft_strlen(argv[1]));
	cmd[0] = argv[1];
	cmd[1] = malloc(sizeof(**cmd) * 1);
	cmd[1] = 0;
	//cmd[1] = malloc(sizeof(*cmd[0]) * ft_strlen(argv[2]));
	//cmd[1] = argv[2];
	//cmd[2] = malloc(sizeof(*cmd[0]) * 1);
	//cmd[2] = 0;
	
	if (pid == 0)
	{
		while (*path && exe_read == -1)
		{
			exe_read = execve(ft_strcat(*path, *cmd), cmd, path);
			ft_printf("exe_read = %d\n", exe_read);
			path++;
		}
		if (exe_read == -1)
			ft_get_path(NULL);
	}
	return (0);
}
