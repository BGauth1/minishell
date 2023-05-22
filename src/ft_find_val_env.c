/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_val_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:57:23 by lamasson          #+#    #+#             */
/*   Updated: 2023/05/22 14:58:44 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//parse verif double simple quote ou rien 
//recuperer la str verifier
//compter avant compter apres et compter le user correspondant
//malloc taille 
//strjoin

//    ft_display_var_env ----- ft_parsing_simple_double_quote

/*
 * Parsing NAME variable d'environnement bien ecrit
 */

int	ft_check_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$')
		i++;
	i++;
	if (ft_isalpha(str[i]) == 0)
		return (1);
	else
		i++;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0)
			if (str[i] != '_')
				return (1);
		i++;
	}
	return (0);
}

int	ft_check_dollar(char *str) //if 0 good if 1 not good 
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

/*
 *
 */

int	main(int argc, char **argv)
{
	(void)argc;
	int	i = 1;
	
	if (ft_check_dollar(str) == 1)
		return (1);
	if (ft_check_name(str) == 1)
		return (1);

	while (argv[i])
	{
		printf("$----%s = (0) %d\n", argv[i], ft_check_dollar(argv[i]));
		printf("name----%s = (0) %d\n", argv[i], ft_check_name(argv[i]));
		i++;
	}
}
