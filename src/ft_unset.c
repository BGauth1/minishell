/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:00:32 by lamasson          #+#    #+#             */
/*   Updated: 2023/04/27 20:10:18 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//unset MY_VAR MY_VAR1 MY_VAR2 //possible boucle pour executer unset a la suite

int	ft_unset(char *str, t_files *files) //nom variable off //changer losque structur ok
{
	int		i;
	char	*tmp;

	i = 0;
	if (!str || getenv(str) == NULL)
	{
		//return un prompt et ne se passe rien
		return (0);
	}
	while (ft_strncmp(files->tab_var_env[i], str, ft_strlen(str)) != 0) //if (str)
		i++;
	free(files->tab_var_env[i]);
	while (files->tab_var_env[i] != NULL)
	{
		tmp = files->tab_var_env[i + 1];
		files->tab_var_env[i] = tmp;
		i++;
	}
	return (0);
}
