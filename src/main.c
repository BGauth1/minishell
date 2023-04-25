/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:27:42 by gbertet           #+#    #+#             */
/*   Updated: 2023/04/25 18:49:52 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		*has_here_doc(char *s, int nb_cmds)
{
	int	*here_doc;
	int	n;
	int	i;

	n = 0;
	i = 0;
	here_doc = malloc(nb_cmds * sizeof(int));
	while (n < nb_cmds)
	{
		here_doc[n] = 0;
		n++;
	}
	n = 0;
	while (n < nb_cmds && s[i])
	{
		if (s[i] == '|' && !ft_betweenquotes(s, i))
			n++;
		else if (s[i] == '<' && s[i + 1] == '<' && !ft_betweenquotes(s, i))
		{
			here_doc[n] = 1;
			i++;
		}
		i++;
	}
	return (here_doc);
}

int		get_nb_cmds(char *s)
{
	int	n;
	int	i;

	n = 1;
	i = 0;
	while (ft_iswhitespace(s[i]))
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == '|' && !ft_betweenquotes(s, i))
		{
			n++;
			i++;
			while (ft_iswhitespace(s[i]))
				i++;
			if (s[i] == '|' || !s[i])
				return (n);
			i--;
		}
		i++;
	}
	return (n);
}

void	get_cmds(t_mishell *m)
{
	int	i;
	int	j;

	m->nb_cmds = get_nb_cmds(m->full_cmd);
	m->here_doc = has_here_doc(m->full_cmd, m->nb_cmds);
	m->cmd = malloc((m->nb_cmds + 1) * sizeof(char **));
	m->cmd[m->nb_cmds] = NULL;
}

int empty_str(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (1);
	while (ft_iswhitespace(s[i]))
		i++;
	if (!s[i])
		return (1);
	return (0);
}

int main(int ac, char **av, char **ev)
{
	t_mishell	mish;
	char		*prompt;
	char		*tmp;

	if (getcwd(mish.path, sizeof(mish.path)) == NULL)
    {
        perror("getcwd");
        return (1);
    }
	while (1)
	{
		prompt = ft_strjoin(mish.path, "$ ");
		tmp = ft_readline(prompt);
		if (empty_str(tmp))
			printf("\n");
		else
		{
			mish.full_cmd = normalize_str(tmp);
			printf("%s\n", mish.full_cmd);
			get_cmds(&mish);
		}
		free(tmp);
		free(prompt);
	}
}