/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:09:03 by lamasson          #+#    #+#             */
/*   Updated: 2023/05/16 19:25:55 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return une string malloc avec le nom
 * du fichier d'entrer ou de sortit*/

char	*rec_file(char *str, int i)
{
	int		y;
	char	*file;

	y = i;
	while (ft_iswhitespace(str[y]) == 0)
		y++;
	file = ft_substr(str, i, y - i);
	if (file == NULL)
		exit (1); //fct de free necessaire suivant pos dans cod
	return (file);
}

/* check redirection out
 * if classic or append mode:
 * '>' '>>' '>>>'
 * return int out; in struct files
 * si 1 out = 0
 * si 2 out = 1 (output append mode)
 * si 3 exit print error*/

int	redirect_out(char *str, int *i)
{
	int	out;

	(*i)++;
	if (str[*i] == '>')
	{
		out = 1;
		(*i)++;
		if (str[*i] == '>')
		{
			printf("minsihell: syntax error near unexpected token `>'\n");
			exit (1);
		}
	}
	else
		out = 0;
	return (out);
}

/* cherche redirection in dans str:
 * str est la string passé dans le terminal,
 * t_files *fd est la struct ou sont stockés
 * le fd du fichier in et du fichier out
 *
 * fct ne check pas d'erreur pour le moment
 * puisque check du here doc dans ft_parsing_cmd.c
 *
 * if fd_in trouvé malloc puis placé dans struct files
 * else fd_in = NULL*/

int	find_redirect_left(char *str, t_files *fd)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			i++;
			while (ft_iswhitespace(str[i]) == 1)
				i++;
			fd->fd_in = rec_file(str, i);
			return (0);
		}
		i++;
	}
	fd->fd_in = NULL;
	return (1);
}

/* same left-right exept for int out;
 * mis a -1 if no redirection de sortit
 * et fd_out = NULL*/

int	find_redirect_right(char *str, t_files *fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			fd->out = redirect_out(str, &i);
			while (ft_iswhitespace(str[i]) == 1)
				i++;
			fd->fd_out = rec_file(str, i);
			return (0);
		}
		i++;
	}
	fd->out = -1;
	fd->fd_out = NULL;
	return (1);
}

/* fct regroupe parsing redirection in-out,
 * check int et out chmod
 * et recuperation du nom des fichiers fd_in et fd_out
 * dans struct files*/

t_files	parsing_fd(char *str)
{
	t_files	fd;

	find_redirect_left(str, &fd);
	find_redirect_right(str, &fd);
	fd.nb_pipe = 0; //nb_pipe = besoin d'une fct compte le nb de pipre
	if (fd.nb_pipe > 0)
	{
		ft_check_fdout(fd);
		ft_check_fdin(fd);
	}
	else
	{
		ft_check_fdin(fd);
		ft_check_fdout(fd);
	}
	return (fd);
}
/* main_test parsing_redirection.c et parsing_right_file.c
 *
int main(void)
{
	char *str = "<<< test/test.c cat | cat >> test1.c";
	t_files fd;	

	fd = parsing_fd(str);
	printf("%s\n", fd.fd_in);
	printf("%s\n", fd.fd_out);
	printf("%d\n", fd.out);

}*/
