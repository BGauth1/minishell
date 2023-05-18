/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:08:33 by lamasson          #+#    #+#             */
/*   Updated: 2023/05/17 18:02:49 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//ft_readline en test

/* cd en 2 parti : 1 avec un path
 * malloc ".." et 1 avec un path ptr (other)
 * 1er l.27 malloc/free : 2e l.38 ptr
 * 1er appel chdir puis free, 2e chdir sans free
 * puis retourne prompt readline */

int	ft_cd(char **c)
{
	char	*path;

	if (c[2] == NULL)
		path = NULL;
	else if (ft_strncmp(c[2], "..", ft_strlen(c[1])) == 0 && ft_strlen(c[2]) == 2)
	{
		path = rec_parent_file();
		if (ft_chdir(c, path) == 1)
		{
			free(path);
			return (1);
		}
		free(path);
		return (0);
	}
	else
		path = ft_parsing_cd(c);
	if (path == NULL)
		return (0);
	if (ft_chdir(c, path) == 1)
		return (1);
	//ft_path_pos_prompt();
	return (0);
}

/* chdir erreur */

int	ft_chdir(char **c, char *path)
{
	if (chdir(path) != 0)
	{
		printf("minishell: %s: %s: %s\n", c[0], path, strerror(errno));
		return (1);
	}
	return (0);
}

/* Recupere path pour "cd .."
 * pwd = ptr sur var_env, malloc = pb, 
 * donc conserver un ptr vers string,
 * recup PWD, et return path parent */

char	*rec_parent_file(void)
{
	char	*pwd;
	int		len;

	pwd = malloc(sizeof(char *) * 1024);
	if (pwd == NULL)
		exit (1);
	if (getcwd(pwd, 1024) == NULL)
	{
		perror(strerror(errno));
		free(pwd);
		exit (1);
	}
	len = ft_strlen(pwd);
	while (len > 0)
	{
		if (pwd[len] == '/')
		{
			pwd[len] = '\0';
			break ;
		}
		pwd[len] = '\0';
		len--;
	}
	return (pwd);
}

/* parsing chemin relatif particulier
 * ex : '.' '-' 'chemin rela/absolue'
 * cd seul pas a gerer 
 * return c[1] chemin absolu */

char	*ft_parsing_cd(char **c)
{
	int		len;
	char	*path;
	char	*arg;

	arg = c[2]; //c[1] vrai valeur / c[2] only for test
	len = ft_strlen(arg);
	if (ft_strncmp(arg, ".", len) == 0 && len == 1) //ne fait rien
		return (NULL);
	else if (ft_strncmp(arg, "-", len) == 0 && len == 1) //$OLD_PWD+print OLD_PWD
	{
		path = getenv("OLDPWD");
		if (path == NULL)
			exit (1);
		printf("%s\n", path);
	}
	else
		return (arg);
	return (path);
}
