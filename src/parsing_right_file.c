/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_right_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:54:57 by lamasson          #+#    #+#             */
/*   Updated: 2023/04/25 18:56:07 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_fdin(t_files fd) 
{
	int	fd_in;
	
	if (fd.fd_in == NULL)
		return (1);
	fd_in = open(fd.fd_in, O_RDONLY);
	if (fd_in == -1)
	{
		//perror(fd.fd_in);
		printf("minishell: %s: %s\n", fd.fd_in, strerror(errno));
		exit (1);
	}
	close(fd_in);
	return (0);
}

int	ft_check_fdout(t_files fd)
{
	int	fd_out;

	if (fd.fd_out == NULL)
		return (1);
	fd_out = open(fd.fd_out, O_RDWR);
	if (fd_out == -1)
	{
		fd_out = open(fd.fd_out, O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			//perror(fd.fd_out);
			printf("minishell: %s: %s\n", fd.fd_out, strerror(errno));
			if (fd.nb_pipe > 0)
				ft_check_fdin(fd);
			exit (1);
		}
	}
	close (fd_out);
	return (0);
}
