/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:00:45 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/19 21:12:01 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include "parser_print.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <term.h>
# include <termios.h>
# include "env.h"
# include "builtins.h"

# define WORD	0x0001
# define LESS	0x0002
# define GREAT	0x0004
# define DGREAT	0x0008
# define PIPE	0x0010
# define SCOLON	0x0020
# define EXPAN	0x0040
# define TOGET	0x0080

# define EXPORT_VAR	0x0001
# define ENV_VAR	0x0002
/*
typedef struct s_variable
{
	char	*name;
	char	*value;
	int		flags;
}			t_var;
*/
typedef struct s_shell
{
	char			*prompt;
	t_list			*pipeline_lst;
	struct termios	term;
	struct termios	my_term;
	t_list			*env_lst;
	t_env			_env;
	int				status;
}					t_shell;

typedef struct s_path
{
	char			*env;
	char			*dir;
	char			*exe;
}					t_path;

typedef struct s_fd
{
	int		fd[2];
	int		std_fd[2];
	int		redir_fd[2];
	int		piped;
}			t_fd;

typedef struct s_lex
{
	int		start;
	int		len;
	int		i;
}			t_lex;

typedef struct s_word
{
	char	*str;
	int		flags;
}			t_word;

typedef struct s_redirection
{
	char	*file;
	int		type;
}			t_redir;

typedef struct s_command
{
	t_list	*args_lst;
	t_list	*redir_lst;
	int		pipe;
}			t_cmd;

typedef struct s_pipeline
{
	t_list	*cmd_lst;
}			t_pip;

typedef struct s_token
{
	char	*token;
	int		identifier;
}			t_token;

int		is_export(t_var *var);
int		is_env(t_var *var);
char	*join_var(t_var *var);
char	*get_env(char *name, t_list	*var_lst);
t_list	*capture_env(char **env);

/*		builtin			*/

//int		set_env_delete(t_lista *lst, char *str);
int		builtin_echo(t_shell *sh, char **argv);

int		check_builtin(t_shell *sh, int argc, char **argv);
int		builtin_cd(t_shell *sh, int argc, char **argv);
int		builtin_exit(t_shell *sh, int argc, char **argv);
void	print_builtin_error(t_shell *sh, char **argv, char *str, int status);

/*		token			*/

t_token	*new_token(char *str);
int		id_token(char *str);
void	free_token(void *tkn);
void	print_token(void *tkn);
void	del_current_token(t_list **tkn_lst);

/*		quoted			*/

void	args_have_quotes(t_list *lst, t_shell *sh);
int		redir_file_have_quotes(char **str, t_shell *sh);

/*		parser			*/

t_list	*parser(char *input, char *prompt);
t_list	*parse_pipeline(t_list **tkn_lst, char *prompt);
t_pip	*new_pipeline(t_list **tkn_lst, char *prompt);
t_list	*parse_command(t_list **tkn_lst, char *prompt);
t_cmd	*new_simple_command(t_list **tkn_lst, char *prompt);
void	parse_args(t_list **tkn_lst, t_list **args_lst);
int		parse_redir(t_list **tkn_lst, t_cmd *cmd, int id, char *prompt);
t_redir	*new_redirection(t_list **tkn_lst, int type, char *prompt);
int		parse_pipe(t_list **tkn_lst, t_cmd *cmd, int *pipe, char *prompt);
void	print_syntax_error(char *token, t_list **tkn_lst, char *prompt);
void	free_redir(void *redir);
void	free_command(void *cmd);
void	free_pipeline(void *pipeline);

/*		lexer			*/

t_list	*tokenizer(char *input);
int		skip_to_delimiter(char *str, char *set, int *len);
void	is_quoted(char c, int *quoted);

/*		fd				*/

void	set_fd(int *fd, int id);
void	cpy_std_fd(int *fd);
void	reset_std_fd(int *fd);
void	set_std_fd(t_fd *fd, int id);
void	set_pipe(int *fd, int *piped);

/*		executer		*/

void	executer(t_shell *sh);
void	executer_pipeline(t_pip *pipeline, t_shell *sh, t_fd *fd);
int		set_redir_fd(t_list *redir_lst, int *fd, t_shell *sh);
void	print_file_error(char *file, char *prompt);
void	find_command(t_cmd *cmd, t_shell *sh);

/*		command			*/

int		search_directory(char *path, char *name);
char	*get_exe_path(char *name, t_shell *sh);
int		executer_command(t_shell *sh, char *path, char **argv, char **env);
void	print_command_error(char *cmd, char *prompt, int *status);

/*		main			*/

void	print_prompt(char *prompt);
char	*read_command_line(void);
void	read_eval_print_loop(t_shell *sh);
void	print_error(t_shell *sh, char *str, char *msg, int status);

#endif
