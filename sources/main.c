/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:19:28 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/14 18:51:08 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include <stdio.h>
#include "libftprintf.h"
#include "not_my_libft.h"

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

int	main(int argc, char **argv, char **envp)
{
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
