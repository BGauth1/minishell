/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:59:08 by gbertet           #+#    #+#             */
/*   Updated: 2023/06/29 15:30:49 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_less_whitespace(char *s)
{
	int		i;
	int		tmp;
	char	*res;

	i = 0;
	res = ft_strdup(s);
	while (res[i])
	{
		if (ft_iswhitespace(res[i]) && ft_iswhitespace(res[i + 1]) && !ft_betweenquotes(res, i))
		{
			tmp = i;
			while (res[tmp])
			{
				res[tmp] = res[tmp + 1];
                tmp++;
			}
			res[i] = ' ';
		}
		else
			i++;
	}
	return (res);
}

char	*remove_char(char *s, int pos)
{
	while (s[pos])
	{
		s[pos] = s[pos + 1];
        	pos++;
	}
	s[ft_strlen(s)] = '\0';
	return (s);
}

char	*add_char_right(char *s, int pos)
{
	int	i;

	i = ft_strlen(s);
	if (!i)
		return (NULL);
	s = ft_realloc(s, i, i + 1);
	s[i + 1] = '\0';
	while (i != pos)
	{
		s[i] = s[i - 1];
		i--;
	}
	s[pos] = ' ';
	return (s);
}

char	*format_str_spaces(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_betweenquotes(s, i))
		{
			if (s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != ' ')
			{
				if ((s[i + 1] == '|')
					&& !ft_betweenquotes(s, i + 1))
					s = add_char_right(s, i + 1);
			}
			else if (s[i] == '|' && s[i + 1] != ' ')
				s = add_char_right(s, i + 1);
			else if (s[i] == '<' || s[i] == '>')
			{
				if (s[i + 1] != '<' && s[i + 1] != '>' && s[i + 1] != ' '
					&& s[i + 1])
					s = add_char_right(s, i + 1);
			}
		}
	}
	return (s);
}

char	*normalize_str(char *s, t_files *files)
{
	int	i;
	int	j;
	char	*res;
	char	*tmp;

	i = 0;
	j = ft_strlen(s) - 1;
	while (ft_iswhitespace(s[i]))
		i++;
	while (j > 0)
	{
		if (!ft_iswhitespace(s[j]))
			break;
		j--;
	}
	tmp = ft_substr(s, i, j - i + 1);
	res = ft_less_whitespace(tmp);
	free(tmp);
	res = format_str_spaces(res);
	if (check_pipe(s))
	{
		g_status = 2;
		free(res);
		printf("Synthax error near unexpected token '|'.\n");
		return (NULL);
	}
	res = ft_handle_var_env(res, *files);
	res = format_str_spaces(res);
	// res = ft_remove_quotes(res);
	return (res);
}

int	ft_nb_redir(char **cmd)
{
	int		i;
	int		size;

	i = -1;
	size = ft_strstrlen(cmd);
	while (cmd[++i])
	{
		if (!ft_strncmp(cmd[i], "<", 1) || !ft_strncmp(cmd[i], ">", 1))
		{
			i++;
			size -= 2;
		}
	}
	return (size);
}

char	*ft_remove_quotes(char *s)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	while (s[i])
	{
		if (!c && (s[i] == '\'' || s[i] == '\"'))
		{
			c = s[i];
			s = remove_char(s, i);
		}
		else if (c == s[i])
		{
			c = '\0';
			s = remove_char(s, i);
		}
		else
			i++;
	}
	return (s);
}

char	**ft_remove_redirections(char **cmd)
{
	int		i;
	int		j;
	int		size;
	char	**res;

	i = -1;
	size = ft_nb_redir(cmd);
	res = malloc((size + 1) * sizeof(char *));
	res[size] = NULL;
	j = 0;
	while (cmd[++i])
	{
		if (ft_strncmp(cmd[i], "<", 1) && ft_strncmp(cmd[i], ">", 1))
			res[j++] = ft_strdup(cmd[i]); ///(ft_remove_quotes(cmd[i]));
		else
			i++;
	}
	ft_free_str(cmd);
	return (res);
}
