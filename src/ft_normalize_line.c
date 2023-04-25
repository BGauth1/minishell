/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:59:08 by gbertet           #+#    #+#             */
/*   Updated: 2023/04/25 18:08:11 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_less_whitespace(char *s)
{
	int		i;
	int		tmp;
	char	*res;

	i = 0;
	res = ft_strdup(s);
	while (res[i])
	{
		if (ft_iswhitespace(res[i]) && ft_iswhitespace(res[i + 1]) && !ft_betweenquotes(res, i))
		{
			tmp = i;
			while (res[tmp])
			{
				res[tmp] = res[tmp + 1];
                tmp++;
			}
		}
		else
			i++;
	}
	return (res);
}

char	*normalize_str(char *s)
{
	int	i;
	int	j;
	char	*res;
	char	*tmp;

	i = 0;
	j = ft_strlen(s) - 1;
	while (ft_iswhitespace(s[i]))
		i++;
	while (j > 0)
	{
		if (!ft_iswhitespace(s[j]))
			break;
		j--;
	}
	tmp = ft_substr(s, i, j - i + 1);
	res = ft_less_whitespace(tmp);
	free(tmp);
	return (res);
}