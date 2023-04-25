/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:52:20 by gbertet           #+#    #+#             */
/*   Updated: 2023/04/25 18:45:29 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == '|' && !ft_betweenquotes(s, i))
		{
			if (s[i + 1] == '|' || !s[i + 1])
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_here_doc(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<' && !ft_betweenquotes(s, i))
		{
			if (s[i + 2] == '<' || !s[i + 2])
				return (0);
		}
		i++;
	}
	return (1);
}

int synthax_check(const char *s)
{
	if (!check_pipe(s))
		return (0);
	if (!check_here_doc(s))
		return (0);
	return (1);
}