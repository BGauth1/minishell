/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:53:32 by gbertet           #+#    #+#             */
/*   Updated: 2023/04/25 15:12:53 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*	Return 1 si le char s[pos] est entre des
	doubles/simples quotes, sinon return 0.	*/
int ft_betweenquotes(char *s, int pos)
{
	int		i;
	int		quote;
	char	c;

	i = -1;
	quote = 0;
	c = '\0';
	if (!s)
		return (0);
	if (ft_strlen(s) <= pos)
		return (0);
	while (s[++i])
	{
		if (i == pos)
			return (quote);
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

int ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}