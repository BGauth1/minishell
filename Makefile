# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 17:11:07 by lamasson          #+#    #+#              #
#    Updated: 2023/07/05 18:07:09 by gbertet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## COLORS ##########

_END="\033[0m"
_RED="\033[0;31m"
_GREEN="\033[0;32m"
_YELLOW="\033[0;33m"
_CYAN="\033[0;36m"

########## ARGUMENTS ##########

NAME		= minishell
CXX			= clang
CXXFLAGS	= -Wall -Werror -Wextra -g

########## SOURCES ##########

SRC_DIR		= src
OBJ_DIR		= obj
BIN_DIR		= bin

MAKEFLAGS	+= --no-print-directory
SRC			= src/ft_check_builtins.c \
			src/pipex/ft_exec.c \
			src/pipex/ft_get_path_cmd.c \
			src/var_env/ft_init_tab_env.c \
			src/var_env/ft_maj_tab_env.c \
			src/parsing/ft_normalize_line.c \
			src/parsing/ft_normalize_line_utils.c \
			src/parsing/ft_parsing_cmd.c \
			src/pipex/ft_pipex.c \
			src/ft_readline.c \
			src/parsing/ft_split_minishell.c \
			src/pipex/ft_strjoin_path.c \
			src/parsing/ft_utils.c \
			src/main.c \
			src/ft_get_cmds.c \
			src/ft_free.c \
			src/redirection/parsing_redirection.c \
			src/redirection/parsing_right_file.c \
			src/built/ft_cd.c \
			src/built/ft_echo.c \
			src/built/ft_env.c \
			src/built/ft_exit.c \
			src/built/ft_export.c \
			src/built/ft_export_utils.c \
			src/built/ft_export_algo.c \
			src/built/ft_pwd.c \
			src/built/ft_unset.c \
			src/var_env/ft_parsing_var_env.c \
			src/var_env/ft_parsing_var_env_utils.c \
			src/var_env/ft_join_var_env_str.c \
			src/signal/signal.c \
			src/redirection/ft_heredoc.c \
			src/pipex/ft_pipex_utils.c \
			src/built/ft_export_parsing.c 

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT		= libft
INC			= -Iinc

########## RULES ##########

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo $(_GREEN)Compiling $(OBJ)...$(END)
	@echo $(_GREEN)Compiling libft
	@$(MAKE) bonus -C $(LIBFT)
	@$(CXX) $(CXXFLAGS) -L $(LIBFT) -o $(NAME) $(OBJ) -lreadline -l:libft.a

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo $(_CYAN)Compiling $<...$(END)
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	@echo $(_YELLOW)Cleaning $(OBJ)...$(END)
	@rm -rf $(OBJ_DIR)
	@echo $(-_YELLOW)Cleaning libft
	@$(MAKE) -s -C $(LIBFT) clean

fclean: clean
	@echo $(_RED)Cleaning $(NAME)...$(END)
	@rm -rf $(NAME)
	@echo $(_RED)Cleaning libft.a
	@$(MAKE) -s -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re

