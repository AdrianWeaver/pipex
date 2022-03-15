/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:00:47 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/15 11:55:22 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libftprintf.h"
#include "ft_pipex.h"
#include "not_my_libft.h"

int	ft_open_inputfile(char *infile, char **path)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		dup2(1, STDOUT_FILENO);
		ft_printf("%s: %s\n", strerror(errno), infile);
		ft_free_path(path);
		exit (1);
	}
	return (infile_fd);
}

int	ft_open_outputfile(char *outfile, char **path)
{
	int	outfile_fd;

	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile_fd == -1)
	{
		dup2(1, STDOUT_FILENO);
		ft_printf("%s: %s\n", strerror(errno), outfile);
		ft_free_path(path);
		exit (1);
	}
	return (outfile_fd);
}
