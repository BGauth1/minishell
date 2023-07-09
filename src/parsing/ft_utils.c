/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:53:32 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/09 15:20:53 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_betweenchar(char *s, int pos, char cquote)
{
	int		i;
	int		quote;
	char	c;

	i = -1;
	quote = 0;
	c = '\0';
	if ((int)ft_strlen(s) <= pos)
		return (0);
	while (s[++i])
	{
		if (i == pos)
			return (quote && s[i] != c && c == cquote);
		else if (!quote && (s[i] == '\'' || s[i] == '\"'))
		{
			quote = 1;
			c = s[i];
		}
		else if (quote && s[i] == c)
			quote = 0;
	}
	return (0);
}

int	ft_betweenquotes(char *s, int pos)
{
	if (pos < 0)
		return (0);
	return (ft_betweenchar(s, pos, '\'') || ft_betweenchar(s, pos, '\"'));
}

int	ft_strstrlen(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	**ft_strstrdup(char **s)
{
	int		i;
	char	**res;

	i = 0;
	while (s[i])
		i++;
	res = malloc((i + 1) * sizeof (char *));
	i = 0;
	while (s[i])
	{
		res[i] = ft_strdup(s[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
