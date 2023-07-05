/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_line_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:02:41 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/05 18:09:22 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_less_whitespace(char *s)
{
	int		i;
	int		tmp;
	char	*res;

	i = 0;
	res = ft_strdup(s);
	while (res[i])
	{
		if (ft_iswhitespace(res[i]) && ft_iswhitespace(res[i + 1])
			&& !ft_betweenquotes(res, i))
		{
			tmp = i;
			while (res[tmp])
			{
				res[tmp] = res[tmp + 1];
				tmp++;
			}
			res[i] = ' ';
		}
		else
			i++;
	}
	return (res);
}

char	*remove_char(char *s, int pos)
{
	while (s[pos])
	{
		s[pos] = s[pos + 1];
			pos++;
	}
	s[ft_strlen(s)] = '\0';
	return (s);
}

char	*ft_add_char(char *s, char c, int pos)
{
	int	i;

	i = ft_strlen(s);
	if (!i)
		return (NULL);
	s = ft_realloc(s, i, i + 1);
	s[i + 1] = '\0';
	while (i != pos)
	{
		s[i] = s[i - 1];
		i--;
	}
	s[pos] = c;
	return (s);
}

int	nb_end_whitespace(char *s)
{
	int	j;

	j = ft_strlen(s) - 1;
	while (j > 0)
	{
		if (!ft_iswhitespace(s[j]))
			break ;
		j--;
	}
	return (j);
}
