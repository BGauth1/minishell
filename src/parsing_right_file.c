/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_right_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:54:57 by lamasson          #+#    #+#             */
/*   Updated: 2023/05/16 19:26:30 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check si fd_in accessible
 * erreur chmod */

int	ft_check_fdin(t_files fd)
{
	int	fd_in;

	if (fd.fd_in == NULL)
		return (1);
	fd_in = open(fd.fd_in, O_RDONLY);
	if (fd_in == -1)
	{
		printf("minishell: %s: %s\n", fd.fd_in, strerror(errno));
		exit (1);
	}
	close(fd_in);
	return (0);
}

/* check si fd_out accessible
 * erreur chmod et creation du
 * fichier de sortit si necessaire
 * et si possible*/

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
			printf("minishell: %s: %s\n", fd.fd_out, strerror(errno));
			if (fd.nb_pipe > 0)
				ft_check_fdin(fd);
			exit (1);
		}
	}
	close (fd_out);
	return (0);
}
