/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:19:28 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/14 16:58:17 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include <stdio.h>
#include "libftprintf.h"
#include "not_my_libft.h"

void	ft_check_params(int argc)
{
	if (argc < 2)
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

int	ft_exec_child(char **path, char **cmd1, char **cmd2, int infile_fd, int outfile_fd)
{
	int		i;
	int		exe_read;
	int		pid;
	int		pipe_fd[2];
	int		w_status;

	i = 0;
	exe_read = -1;
	pipe(pipe_fd);
	pid = fork();
	wait(&w_status);
	if (pid == 0)
	{
		ft_free_cmd(cmd2);
		dup2(infile_fd, STDIN_FILENO);
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[READ_END]);
		while (path[i] && exe_read == -1)
		{
			if (access(path[i], X_OK) == 0)
			{
				exe_read = execve(ft_strcat(path[i], *cmd1), cmd1, path);
			}
			i++;
		}
		ft_check_execve(path, cmd1, exe_read);
		close(infile_fd);
	}
	else if (pid != 0 && WIFEXITED(w_status) == 1 && WEXITSTATUS(w_status) != -1)
	{
		ft_free_cmd(cmd1);
		dup2(outfile_fd, STDOUT_FILENO);
		dup2(pipe_fd[READ_END], STDIN_FILENO);
		close(pipe_fd[WRITE_END]);
		while (path[i] && exe_read == -1)
		{
			if (access(path[i], X_OK) == 0)
				exe_read = execve(ft_strcat(path[i], *cmd2), cmd2, path);
			i++;
		}
		ft_check_execve(path, cmd2, exe_read);
		close(outfile_fd);
	}
	//dup2(1, STDOUT_FILENO);
	ft_free_cmd(cmd2);
	return (0);
}

int	ft_open_inputfile(char *infile, char **path)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		ft_printf(RED"File given as input doesnt exist or is forbidden\n"
			NOCOLOUR);
		perror("open returned");
		ft_free_path(path);
		exit (-1);
	}
	return (infile_fd);
}

int	ft_open_outputfile(char *outfile, char **path)
{
	int	outfile_fd;

	outfile_fd = open(outfile, O_RDWR | O_CREAT, 0666);
	if (outfile_fd == -1)
	{
		ft_printf(RED"File given as output does not exist or is forbidden\n"
			NOCOLOUR);
		perror("open returned");
		ft_free_path(path);
		exit (-1);
	}
	return (outfile_fd);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_data	data;
	char			**path;
	char			**cmd1;
	char			**cmd2;
	int				infile_fd;
	int				outfile_fd;
	int				w_status;
	int				pid;

	ft_check_params(argc);
	path = ft_get_path(envp);
	pid = fork();
	if (pid == -1)
		ft_fork_fail(path);
	wait(&w_status);
	if (pid == 0)
	{
		infile_fd = ft_open_inputfile(argv[1], path);
		outfile_fd = ft_open_outputfile(argv[4], path);
		cmd1 = ft_get_cmd(argv[2]);
		cmd2 = ft_get_cmd(argv[3]);
		ft_exec_child(path, cmd1, cmd2, infile_fd, outfile_fd);
	}
	ft_free_path(path);
	return (0);
}
