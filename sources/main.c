/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:19:28 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/11 18:09:43 by aweaver          ###   ########.fr       */
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
				return (0); //make error handle program
			tmp = ft_strcpy(tmp, path[i]);
			tmp[path_len] = '/';
			tmp[path_len + 1] = 0;
			free(path[i]);
			path[i] = tmp;
		}
		//ft_printf("PATH : %s\n", path[i]);
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

void	ft_free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

char	**ft_get_cmd(char *argv)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	return (cmd);
}

int ft_pipe_stdout(int *pipefd)
{
    int stdout_save;

    stdout_save = dup(STDOUT_FILENO);
    pipe(pipefd);
    dup2(pipefd[WRITE_END], STDOUT_FILENO);
    close(pipefd[WRITE_END]);
    return (stdout_save);
}

int	ft_pipe_stdin(int *pipefd, int infile_fd)
{
	int	stdin_save;

	stdin_save = dup(STDIN_FILENO);
	pipe(pipefd);
	dup2(pipefd[WRITE_END], infile_fd);
	//close(pipefd[WRITE_END]); 
	dup2(pipefd[READ_END], STDIN_FILENO);
	//close(pipefd[READ_END]);
	return (stdin_save);
}

void    ft_reset_stdout(int *fd_pipe, int stdout_save)
{
    dup2(stdout_save, STDOUT_FILENO);
    close(fd_pipe[READ_END]);
}

int	ft_exec_child(char **path, char **cmd, int infile_fd, int outfile_fd)
{
	int		i;
	int		exe_read;
	int		pid;
	int		pipe_fd[2];

	i = 0;
	exe_read = -1;
	pipe(pipe_fd);
	pid = fork(); //child writes parent reads
	if (pid == 0)
	{
		dup2(infile_fd, STDIN_FILENO);
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[READ_END]);
		while (path[i] && exe_read == -1)
		{
			if (access(path[i], X_OK) == 0)
				exe_read = execve(ft_strcat(path[i], *cmd), cmd, path);
			i++;
		}
		close(infile_fd);
	}
	else if (pid != 0)
	{
		dup2(outfile_fd, STDOUT_FILENO);
		dup2(pipe_fd[READ_END], STDIN_FILENO);
		close(pipe_fd[WRITE_END]);
		while (path[i] && exe_read == -1)
		{
			if (access(path[i], X_OK) == 0)
				exe_read = execve(ft_strcat(path[i], *cmd), cmd, path);
			i++;
		}
		close(outfile_fd);
	}
	dup2(1, STDOUT_FILENO);
	if (exe_read == -1)
	{
		ft_free_path(path);
		ft_printf(RED"Something went wrong, command wasn't found\n"
			NOCOLOUR);
		free(cmd);
	}
	return (0);
}


void	ft_fork_fail(char **path)
{
	ft_free_path(path);
	ft_printf(RED"The program encountered a critical failure\n");
	exit (0);
}

void	ft_open_inputfile(char *infile)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
		return ; //add error handling
}

int	main(int argc, char **argv, char **envp)
{
	char	**path;
	int		pid;
	int		w_status;
	char	**cmd1;
	char	**cmd2;
	int		infile_fd;
	int		outfile_fd;

	(void)cmd2;
	ft_check_params(argc);
	path = ft_get_path(envp);
	pid = fork();
	if (pid == -1)
		ft_fork_fail(path);
	wait(&w_status);
	if (pid == 0)
	{
		infile_fd = open(argv[1], O_RDONLY);
		outfile_fd = open(argv[4], O_CREAT, O_WRONLY);
		cmd1 = ft_get_cmd(argv[2]);
		cmd2 = ft_get_cmd(argv[3]);
		exit(ft_exec_child(path, cmd1, infile_fd, outfile_fd));
		//ft_exec_child(path, cmd2);
	}
	else
		ft_free_path(path);	
	return (0);
}
