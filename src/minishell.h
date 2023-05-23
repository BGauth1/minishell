/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:30:57 by lamasson          #+#    #+#             */
/*   Updated: 2023/05/23 19:31:20 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h> //fork, wait, waitpid, wait3, wait4, open
# include <sys/wait.h> //wait
# include <fcntl.h> //access, open, unlink
# include <stdio.h> //printf
# include <stdlib.h> //malloc, free, getenv, exit
# include <unistd.h> //write, read, pipe, dup, dup2, execve, getcwd, chdir
# include <readline/readline.h> //readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <readline/history.h>
# include <signal.h> //signal, sigaction, sigemptyset, sigaddset, kill
# include <errno.h> //strerror, perror
# include <sys/stat.h> //stat, lstat, fstat
# include <dirent.h> //opendir, readdir, closedir 
# include <sys/time.h> //?
# include <termios.h> //tcsetattr, tcgetattr, isatty, ttyname, ttyslot, ioctl
# include "../libft/libft.h"

typedef struct s_mishell
{
	struct s_cmd	*cmds;		//tableau de structure des commandes
	char			**av;		//tab argv du main
	char			*full_cmd;	//ligne de cmd du terminal
	char			path[1024];
	int				nb_cmds;	//nombre de commande dans la ligne
	int				type;
	int				*here_doc;
	char			**env;		//variable d'environnements du main 
}               t_mishell;

typedef struct	s_cmd			//tableau de struct
{
	char	**c;				//tableau cmd avc opt et arg pour chaque
	int		here_doc;
}				t_cmd;

typedef struct s_files{
	char	*fd_in;			//string malloc de fd_in "test.c" if NULL no in
	char	*fd_out;		//string malloc de fd_out "test/test1.c" if NULL no out
	int		out;			// -1 = no fichier out / 0 redirection simple / 1 redirection append mode
	int		nb_pipe;		//nb_pipe def ordre de verif (defini manuellement)(a revoir)
	char	**tab_var_env;	//notre tableau de variables d'environnements
}t_files;

//		FT_ENV.C				//
int		ft_env(t_files files);

//		FT_EXPORT.C				//
int		ft_export(char **c, t_files *files);
void	switch_env(t_files *files, char *name, char *str);
char	*rec_var_env(char *str);
int		ft_parse_name(char *str);

//		FT_EXPORT_UTILS.C		//
int		ft_export_no_arg(t_files files);
void	ft_free_n_tab(char **tab, int n);

//		FT_UNSET.C				//
int		ft_unset(char **c, t_files *files);

//		FT_PWD.C				//
int		ft_pwd(char **c);

//		FT_CD.C					//
int		ft_cd(char **c, t_files *files);

//		FT_UTILS.C				//
int		ft_iswhitespace(char c);
int		ft_betweenquotes(char *s, int pos);

//		FT_READLINE.C			//
char	*ft_readline(char *str);
int		ft_path_pos_prompt(void);
char	*ft_read_here_doc(char *prompt, char *eof);

//		FT_NORMALIZE_LINE.C		//
char	*normalize_str(char *s);

//		PARSING_REDIRECTION.C	//
t_files parsing_fd(char *str);

//		PARSING_RIGHT_FILE.C	//
int		ft_check_fdin(t_files fd);
int		ft_check_fdout(t_files fd);

//		PARSING_

//		FT_EXIT.C				//
void	ft_free_str(char **s);
void	ft_free_cmds(t_mishell *m);
void	ft_exit(t_mishell *m);

//		FT_SPLIT_MINISHELL.C	//
char	**ft_split_minishell(char const *s, char c);

//		FT_PARSING_CMD.C		//
int		empty_str(const char *s);
int		synthax_check(char *s);

//		FT_INIT_TAB_ENV.C		//
void	ft_init_tab_env(char **env, t_files *files);
void	ft_free_tab_env(t_files *files);
int		ft_tablen(char **tab);

//		FT_MAJ_TAB_ENV.C		//HOME, USER, _ :pas fait  
int		maj_tab_env_oldpwd(t_files *files); //appel en 1er recup pwd pour ca maj
int		maj_tab_env_pwd(t_files *files);

#endif
