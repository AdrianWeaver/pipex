/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:19:28 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/15 13:09:41 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include <stdio.h>
#include "libftprintf.h"
#include "not_my_libft.h"

int	ft_write_child(t_pipex_data *data, int infile_fd, int *pipe_fd, char **av)
{
	int	exe_read;
	int	i;
	int	save_stdout;

	i = 0;
	exe_read = -1;
	ft_free_cmd(data->cmd2);
	save_stdout = dup(STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close(infile_fd);
	close(pipe_fd[WRITE_END]);
	close(pipe_fd[READ_END]);
	while (data->path[i] && exe_read == -1)
	{
		if (access(data->path[i], X_OK) == 0)
			exe_read = execve(ft_strcat(data->path[i], data->cmd1[0]),
					data->cmd1, data->path);
		i++;
	}
	dup2(save_stdout, STDOUT_FILENO);
	ft_check_execve(data->path, data->cmd1, exe_read, av[2]);
	close(infile_fd);
	return (0);
}

int	ft_read_child(t_pipex_data *data, int outfile_fd, int *pipe_fd)
{
	int	exe_read;
	int	i;
	int	save_stdout;

	i = 0;
	exe_read = -1;
	ft_free_cmd(data->cmd1);
	save_stdout = dup(STDOUT_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	dup2(pipe_fd[READ_END], STDIN_FILENO);
	close(pipe_fd[WRITE_END]);
	while (data->path[i] && exe_read == -1)
	{
		if (access(data->path[i], X_OK) == 0)
			exe_read = execve(ft_strcat(data->path[i], data->cmd2[0]),
					data->cmd2, data->path);
		i++;
	}
	close(pipe_fd[READ_END]);
	dup2(save_stdout, STDOUT_FILENO);
	close(outfile_fd);
	return (exe_read);
}

int	ft_exec_child(t_pipex_data *data, int infile_fd, int outfile_fd, char **av)
{
	int		pid;
	int		pipe_fd[2];
	int		ret_read;
	int		w_status;

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		ft_free_cmd(data->cmd1);
		ft_free_cmd(data->cmd2);
		ft_fork_fail(data->path);
	}
	else if (pid == 0)
	{
		ft_write_child(data, infile_fd, pipe_fd, av);
	}
	else if (pid != 0)
	{
		ret_read = ft_read_child(data, outfile_fd, pipe_fd);
		wait(&w_status);
		ft_check_execve(data->path, data->cmd2, ret_read, av[3]);
		ft_free_cmd(data->cmd2);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_data	data;
	int				infile_fd;
	int				outfile_fd;
	int				w_status;
	int				pid;

	ft_check_params(argc);
	data.path = ft_get_path(envp, argv);
	pid = fork();
	if (pid == -1)
		ft_fork_fail(data.path);
	wait(&w_status);
	if (pid == 0)
	{
		infile_fd = ft_open_inputfile(argv[1], data.path);
		outfile_fd = ft_open_outputfile(argv[4], data.path);
		data.cmd1 = ft_get_cmd(argv[2]);
		data.cmd2 = ft_get_cmd(argv[3]);
		ft_exec_child(&data, infile_fd, outfile_fd, argv);
	}
	ft_free_path(data.path);
	return (0);
}
