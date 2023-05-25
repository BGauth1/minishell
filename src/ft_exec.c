/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:55:00 by lamasson          #+#    #+#             */
/*   Updated: 2023/05/25 17:11:23 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_cmd(t_mishell mish, t_files files)
{


}

//fct parse **c pou obtenir path cmd ou NULL si check builtin//
char	*ft_parse_tab_c(char **c)
{
	

}

char	**ft_get_tab_path(t_files files)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	while (files.tab_var_env[i] && ft_strncmp(files.tab_var_env[i], "PATH=", 5))
			i++;
	if (files.tab_var_env[i] == NULL) //gestion d'erreur
		return (NULL); // si not PATH = var_env PATH a ete unset voir gestion de se cas et si il est possible
	tmp = ft_substr(files.tab_var_env[i], 5, ft_strlen(files.tab_var_env[i]));
	if (!tmp)
		exit (1);
	path = ft_split(tmp, ':');
	free(tmp);
	if (!path)
		exit (1);
	return (path);
}
