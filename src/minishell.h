/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:30:57 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/09 22:02:34 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/time.h>
# include <termios.h>
# include "../libft/libft.h"

extern int	g_status;

typedef struct s_mishell
{
	struct s_cmd	*cmds;
	char			**av;
	char			*full_cmd;
	char			path[1024];
	int				nb_cmds;
	int				pos_cmd;
	int				type;
	int				*here_doc;
	char			**env;
	struct s_files	*files;
	pid_t			*pid;
}t_mishell;

typedef struct s_cmd
{
	struct s_fds	*fds;
	char			**c;
	char			*path;
	int				here_doc;
}t_cmd;

typedef struct s_fds
{
	char	*fd_in;
	char	*fd_out;
	int		in;
	int		out;
	int		err;
}t_fds;

typedef struct s_files
{
	char	**tab_var_env;
	char	**tab_path;
}t_files;

typedef struct s_var_env{
	int					nb_dol;
	char				*str;
	int					len;
	int					pos;
	char				*tmp;
	struct s_new_str	*val;
}t_var_env;

typedef struct s_new_str{
	int		start;
	char	*name;
	int		len_n;
	char	*val;
	int		len_v;
}t_new_str;

//		SRC/FT_CD.C			//
int		ft_cd(char **c, t_files *files);

//		SRC/FT_ECHO.C		//
int		ft_echo(char **cmd);

//		SRC/FT_ENV.C		//
int		ft_env(t_files files, char **c);

//		SRC/FT_EXIT.C		//
int		ft_exit(t_mishell *m);

//	SRC/FT_EXPORT_ALGO.C	//
int		ft_env_cases(t_files *files, char *name, char *c, int n);

//	SRC/FT_EXPORT_PARSING.C	//
int		ft_parse_len(char **c, t_files *files);
int		ft_parse_name_export(char **c, int j);
int		env_var_found(char **tab, char *name, char *c);
void	ft_error_export(char *c, int g, char *cmd);

//	SRC/FT_EXPORT_UTILS.C	//
int		ft_export_no_arg(t_files files);
char	*concat_export(char *env_var, char *str);

//		SRC/FT_EXPORT.C		//
int		ft_export(char **c, t_files *files);
void	switch_env(t_files *files, char *name, char *str);
void	ft_realloc_tab_env(t_files *files, char *str);

//		SRC/FT_PWD.C		//
int		ft_pwd(char **c);

//		SRC/FT_UNSET.C		//
int		ft_unset(char **c, t_files *files);

//	PARSING/FT_NORMALIZE_LINE_UTILS.C	//
int		nb_end_whitespace(char *s);
char	*remove_char(char *s, int pos);
char	*ft_add_char(char *s, char c, int pos);
char	*ft_less_whitespace(char *s);

//		PARSING/FT_NORMALIZE_LINE.C		//
char	*normalize_str(char *s, t_files *files);
char	**ft_remove_redirections(char **cmd);
char	*ft_remove_quotes(char *s);

//		PARSING/FT_PARSING_CMD.C		//
int		empty_str(const char *s);
int		synthax_check(char *s);
int		check_pipe(char *s);

//		PARSING/FT_SPLIT_MINISHELL.C	//
char	**ft_split_minishell(char const *s, char c);

//			PARSING/FT_UTILS.C			//
int		ft_iswhitespace(char c);
int		ft_betweenchar(char *s, int pos, char cquote);
int		ft_betweenquotes(char *s, int pos);
int		ft_strstrlen(char **s);
char	**ft_strstrdup(char **s);

//			PIPEX/FT_EXEC.C			//
void	ft_exec_cmd(t_mishell *mish);

//		PIPEX/FT_GET_PATH_CMD.C		//
char	**ft_get_tab_path(t_files files);
void	ft_init_path_cmd(t_mishell *mish, t_files files, int j);
void	ft_cmd_path_ready(t_mishell *mish);

//		PIPEX/FT_PIPEX_UTILS.C		//
void	ft_check_status_exec(t_mishell *m);
int		open_fdout(t_fds fds);
int		open_fdin(t_mishell *m, int fd_in);
int		ft_check_pipe_and_exit(t_mishell *m);
int		ft_init_tab_pid(t_mishell *m);

//			PIPEX/FT_PIPEX.C			//
int		ft_call_pipex(t_mishell *mish);

//		PIPEX/FT_STRJOIN_PATH.C			//
char	*ft_strjoin_path(char *path, char *cmd);

//		REDIRECTION/FT_HEREDOC.C		//
void	ft_heredoc(char **cmds, t_mishell mish);

//	REDIRECTION/PARSING_REDIRECTION.C	//
t_fds	*parsing_fd(char **str);

//	REDIRECTION/PARSING_RIGHT_FILE.C	//
int		ft_check_fd(char **tmp_fds, int *type);
void	set_fd(char **tmp_fds, t_fds *fds, int *type);

//		SIGNAL.C/SIGNAL.C		//
void	sigint_fork(int signum);
void	sigquit_fork(int signum);
void	signal_maj_outfork(void);

//			VAR_ENV/FT_INIT_TAB_ENV.C		//
void	ft_init_tab_env(char **env, t_mishell *mish);
void	ft_free_tab_env(t_files *files);
int		ft_tablen(char **tab);

//		VAR_ENV/FT_JOIN_VAR_ENV_STR.C		//
void	ft_join_all_str(t_var_env *data);
char	*ft_strjoin_loop(char *tmp, char *buf);
void	ft_val_g_status(t_var_env *data, int j);

//			VAR_ENV/FT_MAJ_TAB_ENV.C		//
int		maj_tab_env_oldpwd(t_files *files);
int		maj_tab_env_pwd(t_files *files);

//		VAR_ENV/FT_PARSING_VAR_ENV_UTILS.C	//
int		ft_check_dollar(char *str, int i);
int		ft_check_end_name(char *str, int i);
void	ft_str_data(char *str, t_var_env *data);
void	ft_free_data_var_env(t_var_env *data, int n);
char	*rec_name_var_env(char *str);

//		VAR_ENV/FT_PARSING_VAR_ENV.C		//
char	*ft_handle_var_env(char *str, t_files files);

//		./FT_CHECK_BUILTINS.C	//
int		check_built_no_fork(char **c, t_files *files, t_mishell *m);
int		check_built_fork(char **c, t_files *files);
int		check_if_cmd_built(t_cmd cmds);

//			./FT_FREE.C			//
void	ft_free_n_tab(char **tab, int n);
void	ft_free_str(char **s);
void	ft_free_cmds(t_mishell *m);
void	ft_free_files(t_mishell *mish);

//		./FT_GET_CMDS.C			//
void	get_cmds(t_mishell *m);

//			FT_READLINE.C		//
char	*ft_readline(char *str);
char	*ft_read_here_doc(char *prompt, char *eof);

#endif
