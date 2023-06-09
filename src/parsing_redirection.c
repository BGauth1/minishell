/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:09:03 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/02 15:34:45 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// char	*rec_file(char *str)
// {
// 	// int		y;
// 	char	*file;

// 	// y = i;
// 	// while (ft_iswhitespace(str[y]) == 0)
// 	// 	y++;
// 	// file = ft_substr(str, i, y - i);
// 	file = ft_strdup(str);
// 	if (file == NULL)
// 		exit (1); //fct de free necessaire suivant pos dans cod
// 	return (file);
// }

int	ft_count_char(char **str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], &c, 1))
			j++;
		i++;
	}
	return (j);
}

int	redirect_type(char *str)
{
	if (!ft_strncmp(str, "<", 2) || !ft_strncmp(str, ">", 2))
		return (0);
	else if (!ft_strncmp(str, "<<", 3) || !ft_strncmp(str, ">>", 3))
		return (1);
	else
	{
		printf("minsihell: syntax error near unexpected token `<'\n");
		exit (1);
	}
	return (-1);
}

char	**find_redirect_left(char **str, t_fds *fds)
{
	int		i;
	int		j;
	char	**fdins;

	i = -1;
	j = ft_count_char(str, '<');
	fdins = malloc((j + 1) * sizeof(char *));
	fdins[j] = NULL;
	j = 0;
	while (str[++i])
	{
		if (!ft_strncmp(str[i], "<", 1))
		{
			fds->in = redirect_type(str[i]);
			if (fds->in == 1)
				fdins[j++] = ft_strdup(".heredoc");
			else
				fdins[j++] = ft_strdup(str[++i]);
		}
	}
	return (fdins);
}

char	**find_redirect_right(char **str, t_fds *fds)
{
	int		i;
	int		j;
	char	**fdouts;

	i = -1;
	j = ft_count_char(str, '>');
	fdouts = malloc((j + 1) * sizeof(char *));
	fdouts[j] = NULL;
	j = 0;
	while (str[++i])
	{
		if (!ft_strncmp(str[i], ">", 1))
		{
			fds->out = redirect_type(str[i]);
			fdouts[j++] = ft_strdup(str[++i]);
		}
	}
	return (fdouts);
}

t_fds	*parsing_fd(char **str)
{
	char	**fdins;
	char	**fdouts;
	t_fds	*fds;

	fds = malloc(sizeof(t_fds));
	fdins = find_redirect_left(str, fds);
	fdouts = find_redirect_right(str, fds);
	fds->err = ft_check_fd(fdins, fdouts, ft_strstrlen(str) - 1);
	if (fds->err == 0)
		set_fd(fdins, fdouts, fds);
	else
	{
		fds->fd_in = NULL;
		fds->fd_out = NULL;
	}
	ft_free_str(fdins);
	ft_free_str(fdouts);
	return (fds);
}

/* main_test parsing_redirection.c et parsing_right_file.c
 */

// int main(void)
// {
// 	char **str;
// 	t_fds fds;

// 	str = malloc(10 * sizeof(char *));
// 	str[9] = NULL;
// 	str[0] = ft_strdup("<");
// 	str[1] = ft_strdup("out");
// 	str[2] = ft_strdup("<");
// 	str[3] = ft_strdup("out");
// 	str[4] = ft_strdup("commande");
// 	str[5] = ft_strdup(">");
// 	str[6] = ft_strdup("ah");
// 	str[7] = ft_strdup(">>");
// 	str[8] = ft_strdup("bh");
// 	parsing_fd(str, &fds);
// 	printf("%s\n", fds.fd_in);
// 	printf("%s\n", fds.fd_out);
// 	printf("%d\n", fds.in);
// 	printf("%d\n", fds.out);
// 	ft_free_str(str);
// 	if (fds.fd_in)
// 		free(fds.fd_in);
// 	if (fds.fd_out)
// 		free(fds.fd_out);
// }
