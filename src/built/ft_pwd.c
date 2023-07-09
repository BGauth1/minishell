/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:02:12 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/09 21:24:41 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_parsing_pwd(char **c)
{
	if (c[1] && c[1][0] == '-')
	{
		ft_error_export(c[1], 2, c[0]);
		return (1);
	}
	return (0);
}

int	ft_pwd(char **c)
{
	char	*pwd;

	if (ft_parsing_pwd(c) != 0)
		return (1);
	pwd = malloc(sizeof(char *) * 1024);
	if (pwd == NULL)
		exit (1);
	if (getcwd(pwd, 1024) == NULL)
	{
		printf("minishell: %s: %s\n", c[0], strerror(errno));
		free(pwd);
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
