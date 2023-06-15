/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_var_env_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:29:51 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/15 15:59:54 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_dollar(char *str, int i)
{
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (i + 1);
	i++;
	}
	return (-1);
}

int	ft_check_end_name(char *str, int i)
{
	while (str[i] != '\0')
	{
		if (str[i - 1] == '$' && str[i] == '?')
		{
			i++;
			break ;
		}
		if (str[i] == '$')
			break ;
		if (str[i] >= 32 && str[i] <= 47)
			break ;
		if (str[i] >= 58 && str[i] <= 64)
			break ;
		if (str[i] >= 91 && str[i] <= 96)
			break ;
		if (str[i] >= 123 && str[i] <= 126)
			break ;
		i++;
	}
	return (i);
}

void	ft_str_data(char *str, t_var_env *data)
{
	while (str[data->len] != '\0')
	{
		if (str[data->len] == '$')
		{
			if (ft_betweenchar(str, data->len, '\'') == 0)
				data->nb_dol++;
		}
		data->len++;
	}
}

char	*rec_name_var_env(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] != '=')
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	name = ft_substr(str, 0, i);
	if (!name)
		exit (1);
	return (name);
}

void	ft_free_data_var_env(t_var_env *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(data->val[i].name);
		if (data->val[i].len_v != 0)
			free(data->val[i].val);
		i++;
	}
	free(data->val);
	free(data->tmp);
	free(data->str);
}
