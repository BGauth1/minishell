/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_var_env_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:29:51 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/06 17:12:10 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_join(char *tmp, char *buf, char *s3)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (tmp && tmp[i] != '\0')
	{
		s3[i] = tmp[i];
		i++;
	}
	while (buf && buf[y] != '\0')
	{
		s3[i] = buf[y];
		i++;
		y++;
	}
	s3[i] = '\0';
}

static char	*ft_strjoin_loop(char *tmp, char *buf)
{
	char	*s3;
	int		len;

	len = ft_strlen(tmp) + ft_strlen(buf);
	s3 = malloc(sizeof(char) * (len + 1));
	if (!s3)
		return (NULL);
	ft_join(tmp, buf, s3);
	if (tmp)
		free(tmp);
	return (s3);
}

void	ft_choose_loop(t_var_env *data, int new_start)
{
	char	*buf;

	buf = NULL;
	if (new_start != data->pos)
	{
		buf = ft_substr(data->str, data->pos, new_start - data->pos);
		data->tmp = ft_strjoin_loop(data->tmp, buf);
		data->pos += ft_strlen(buf);
		free(buf);
	}
}

void	ft_join_all_str(t_var_env *data)
{
	int		new_start;
	int		i;

	i = 0;
	new_start = data->val[i].start - 1;
	data->pos = 0;
	data->tmp = NULL;
	while (i <= data->nb_dol && data->pos < data->len)
	{
		ft_choose_loop(data, new_start);
		if (data->val[i].val != NULL)
		{
			data->tmp = ft_strjoin_loop(data->tmp, data->val[i].val);
			data->pos += data->val[i].len_n + 1;
			i++;
		}
		if (data->val[i].val != NULL)
			new_start = data->val[i].start - 1;
		else
			new_start = data->len;
	}
}
/*
char	*ft_join_all_str(t_var_env *data)
{
	char	*buf = NULL;
	char	*tmp = NULL;
	int		new_start;
	int		end;
	int		i;

	i = 0;
	new_start = data->val[i].start - 1;
	end = 0;	
	while (i <= data->nb_dol && end < data->len)
	{
		if (new_start != end)
		{
			buf = ft_substr(data->str, end, new_start - end);
			if (!tmp)
				tmp = ft_strdup(buf);
			else
				tmp = ft_strjoin_loop(tmp, buf);
			end += ft_strlen(buf);
			free(buf);
		}
		if (data->val[i].new_str != NULL)
		{
			tmp = ft_strjoin_loop(tmp, data->val[i].new_str);
			end += data->val[i].len_n + 1;
			i++;
		}
		if (data->val[i].new_str != NULL)
			new_start = data->val[i].start - 1;
		else
			new_start = data->len;
	}
	return (tmp);
}*/
