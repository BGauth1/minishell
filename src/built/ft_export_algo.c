/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_algo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:32:11 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/05 17:50:02 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_cases(t_files *files, char *name, char *c, int n)
{
	if (n == 1)
		switch_env(files, name, c);
	else if (n == 2)
	{
		free(name);
		return (0);
	}
	else
	{
		free(name);
		ft_realloc_tab_env(files, c);
	}
	return (1);
}
