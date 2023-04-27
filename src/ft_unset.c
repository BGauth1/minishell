/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:00:32 by lamasson          #+#    #+#             */
/*   Updated: 2023/04/27 18:30:36 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **argv, char **env) //nom variable off //changer losque structur ok
{
	int		i;
	char	*tmp;

	i = 0;
	if (!argv[2] || getenv(argv[2]) == NULL)
	{
		//return un prompt et ne se passe rien
		exit (0);
	}
	if (argv[2])
	{
		while (ft_strncmp(env[i], argv[2], ft_strlen(argv[2])) != 0)
			i++;
		while (env[i] != NULL)
		{
			tmp = env[i + 1];
			env[i] = tmp;
			i++;
		}
	}
	return (0);
}