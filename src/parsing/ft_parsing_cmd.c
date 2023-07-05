/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:52:20 by gbertet           #+#    #+#             */
/*   Updated: 2023/06/29 15:05:41 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	check_pipe(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '|')
		return (1);
	while (s[i])
	{
		if (s[i] == '|' && !ft_betweenquotes(s, i))
		{
			if (s[i + 1] == ' ')
				i++;
			if (s[i + 1] == '|' || !s[i + 1])
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_redir(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '<' || s[i] == '>') && (s[i + 1] == '<' ||
			s[i + 1] == '>') && !ft_betweenquotes(s, i))
		{
			if (s[i + 2] == '<' || s[i + 2] == '>' || !s[i + 2])
				return (s[i]);
		}
		else if (!ft_iswhitespace(s[i]))
		{
			if (s[i] != '<' && s[i] != '>' &&
				(s[i + 1] == '<' || s[i + 1] == '>') && !ft_betweenquotes(s, i + 1))
				return (s[i]);
		}
		i++;
	}
	if (s[i - 1] == '>' || s[i - 1] == '<')
		return (s[i - 1]);
	return (0);
}

int	check_quotes(char *s)
{
	int i;
	int sq;
	int	dq;

	i = -1;
	sq = 0;
	dq = 0;
	while (s[++i])
	{
		if (s[i] == '\"' && !ft_betweenquotes(s, i))
			dq++;
		else if (s[i] == '\'' && !ft_betweenquotes(s, i))
			sq++;
	}
	if (dq % 2 == 1)
	{
		printf("Synthax error near unexpected token '\"'.\n");
		return (1);
	}
	else if (sq % 2 == 1)
	{
		printf("Synthax error near unexpected token '\''.\n");
		return (1);
	}
	return (0);
}

int synthax_check(char *s)
{
	// if (check_pipe(s))
	// {
	// 	printf("Synthax error near unexpected token '|'.\n");
	// 	free(s);
	// 	return (0);
	// }
	if (check_redir(s))
	{
		printf("Synthax error near unexpected token '%c'.\n", check_redir(s));
		g_status = 2;
		free(s);
		return (0);
	}
	if (check_quotes(s))
	{
		g_status = 2;
		free(s);
		return (0);
	}
	return (1);
}
