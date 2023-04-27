/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:42:56 by gbertet           #+#    #+#             */
/*   Updated: 2023/04/27 18:46:40 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_files files)
{
	int	i;
	
	i = 0;
	if (!files.tab_var_env)
		return (0);
	while (files.tab_var_env[i])
		printf("%s\n", files.tab_var_env[i++]);
	return (1);
}