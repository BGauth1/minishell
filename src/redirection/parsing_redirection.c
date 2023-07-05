/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:09:03 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/05 18:11:40 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_char(char **str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], &c, 1))
		{
			i++;
			j++;
		}
		else
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

char	**find_redirect_left(char **str, t_fds *fds, int **type)
{
	int		i;
	int		j;
	char	**tmp_fds;

	i = -1;
	j = ft_count_char(str, '<') + ft_count_char(str, '>');
	tmp_fds = malloc((j + 1) * sizeof(char *));
	tmp_fds[j] = NULL;
	j = 0;
	while (str[++i])
	{
		if (str[i][0] == '<')
		{
			fds->in = redirect_type(str[i++]);
			if (fds->in == 1)
				tmp_fds[j] = ft_strdup(".heredoc");
			else
				tmp_fds[j] = ft_strdup(str[i]);
			(*type)[j++] = 1;
		}
		else if (str[i][0] == '>')
		{
			fds->out = redirect_type(str[i]);
			tmp_fds[j] = ft_strdup(str[++i]);
			(*type)[j++] = 2;
		}
	}
	return (tmp_fds);
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
		if (str[i][0] == '>')
		{
			fds->out = redirect_type(str[i]);
			fdouts[j++] = ft_strdup(str[++i]);
		}
	}
	return (fdouts);
}

t_fds	*parsing_fd(char **str)
{
	char	**tmp_fds;
	int		*type;
	t_fds	*fds;

	fds = malloc(sizeof(t_fds));
	type = malloc((ft_count_char(str, '<') + \
		ft_count_char(str, '>') + 1) * sizeof(int));
	tmp_fds = find_redirect_left(str, fds, &type);
	fds->err = ft_check_fd(tmp_fds, type);
	if (fds->err == 0)
		set_fd(tmp_fds, fds, type);
	else
	{
		fds->fd_in = NULL;
		fds->fd_out = NULL;
	}
	free(type);
	ft_free_str(tmp_fds);
	return (fds);
}
