/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_val_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:57:23 by lamasson          #+#    #+#             */
/*   Updated: 2023/05/23 20:00:34 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//parse verif double simple quote ou rien 
//recuperer la str verifier
//compter avant compter apres et compter le user correspondant
//malloc taille 
//strjoin

//    ft_display_var_env ----- ft_parsing_simple_double_quote

/*
 * Parsing NAME variable d'environnement bien ecrit
 */

/* check si $ pour name_var_env si oui
 * return pos '$' si non return -1 pas
 * de var_env */

int	ft_check_dollar(char *str) //if 0 good if 1 not good 
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (-1);
}

/* fct roulette tab_var_env recherche d ela bonne var_env,
 * ? getenv ne peut pas etre utiliser puisqu'il s'appuit sur le vrai env ?
 * ft_getenv_perso qui se repete pour tout le tableau, lorsque tab_env fin 
 * return un nvx name avec un char en - afin de detecter le bon name 
 * ex  : $USERlsjjdc */

char	*ft_wheel_tab_var_env(t_files files, char *name)
{
	int		i;
	int		len_n;
	int		len_tmp;
	char	*tmp;

	i = 0;
	len_n = ft_strlen(name);
	while (files.tab_var_env[i] != NULL)
	{
		tmp = rec_var_env(files.tab_var_env[i]);
		len_tmp = ft_strlen(tmp);
		if (ft_strncmp(tmp, name, len_tmp) == 0)
		{
			tmp = ft_substr(files.tab_var_env[i], len_tmp + 1, len_n - (len_tmp + 1));
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}
/*
	int	i;
	char	*val;

	i = 0;
	val = getenv(name);
	if (val == NULL)
		return (NULL);
	else
		return (val);*/


char	*ft_rec_str_trad(t_files files, char *str, int d)
{
	char 	*new;
	char	*name;
	int		len;

	len = ft_strlen(str);
	while (len > d)
	{
		name = ft_substr(str, d, len - d);
		new = ft_wheel_tab_var_env(files, name);
		if (new != NULL)
			break ;
		free(name);
		len--;
	}
	printf("%s\n", new);
	return (new);
}

/* A gerer : cas '' / ""
 * dif entre: echo $PWD / $PWD 
 * ecrit tout / creer str coller avec mess d'erreur
 * */
int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	int	i = 0;
	t_files	files;
	char *str;

	ft_init_tab_env(env, &files);
	i = ft_check_dollar("$PWD");
	if (i == -1)
		return (1);
	str = ft_rec_str_trad(files, "$PWD", i);
	return (0);
}
