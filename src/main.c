/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:27:42 by gbertet           #+#    #+#             */
/*   Updated: 2023/04/26 19:12:47 by gbertet          ###   ########.fr       */
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

int		ft_count_words(char *s, int n)
{
	int		m;
	int		i;
	int 	nb_words;

	m = 0;
	i = 0;
	while (m != n && s[i])
	{
		if (s[i] == '|' && !ft_betweenquotes(s, i))
			m++;
		i++;
	}
	nb_words = 1;
	if (m == n)
	{
		while (s[i] && (s[i] != '|' || ft_betweenquotes(s, i)))
		{
			if (s[i] == ' ' && s[i + 1] != '|')
				nb_words++;
			i++;
		}
		return (nb_words);
	}
	return (0);
}

char	**ft_fill_cmd(char *s, int n)
{
	char	**res;
	int		nb_words;
	
	nb_words = ft_count_words(s, n);
	res = malloc((nb_words + 1) * sizeof(char *));
	res[nb_words] = NULL;
	return (NULL);
}

void	get_cmds(t_mishell *m)
{
	int	i;
	int	j;

	i = -1;
	m->nb_cmds = get_nb_cmds(m->full_cmd);
	m->here_doc = has_here_doc(m->full_cmd, m->nb_cmds);
	m->cmds = malloc((m->nb_cmds + 1) * sizeof(t_cmd));
	m->cmds[0].c = malloc(2 * sizeof(char *));
	m->cmds[0].c[0] = ft_strdup(m->full_cmd);
	m->cmds[0].c[1] = NULL;
	m->cmds[m->nb_cmds].c = NULL;
	while (++i < m->nb_cmds)
	{
		m->cmds[i].here_doc = m->here_doc[i];
		// m->cmds[i].c = ft_fill_cmd(m->full_cmd, i);
	}
	free(m->here_doc);
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
		free(prompt);
		if (!empty_str(tmp))
		{
			mish.full_cmd = normalize_str(tmp);
			get_cmds(&mish);
			if (!ft_strncmp(mish.full_cmd, "exit", 4))
				ft_exit(&mish);
			ft_free_cmds(&mish);
		}
		free(tmp);
	}
	free(tmp);
	free(prompt);
	free(mish.full_cmd);
}