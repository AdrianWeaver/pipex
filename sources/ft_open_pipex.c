/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:00:47 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/14 18:51:38 by aweaver          ###   ########.fr       */
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
