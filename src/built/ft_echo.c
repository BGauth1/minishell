/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:50:18 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/09 15:26:29 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_newline(char *s)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	if (s[i++] == '-')
	{
		while (s[i] == 'n')
		{
			i++;
			res = 1;
		}
		if (s[i])
			return (0);
		return (res);
	}
	return (0);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (!cmd[1])
	{
		printf("\n");
		return (0);
	}
	while (is_newline(cmd[i]))
	{
		nl = 0;
		if (!cmd[++i])
			break ;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[++i])
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (0);
}
