/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:00:45 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/10 17:05:58 by tsierra-         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <term.h>
# include <termios.h>
# include "env.h"

# define WORD	0x0001
# define LESS	0x0002
# define GREAT	0x0004
# define DGREAT	0x0008
# define PIPE	0x0010
# define SCOLON	0x0020

# define EXPORT_VAR	0x0001
# define ENV_VAR	0x0002

# define EXPORT_BUILTIN	0x0001
# define ENV_BUILTIN	0x0002
# define EXIT_BUILTIN	0x0004
# define CD_BUILTIN		0x0008
# define PWD_BUILTIN	0x0010
# define UNSET_BUILTIN	0x0020
# define ECHO_BUILTIN	0x0040
# define FORK_BUILTIN	0x007B

typedef struct s_exec
{
	char	*path;
	int		argc;
	char	**argv;
	char	**env;
	int		builtin;
}			t_exec;

typedef struct s_shell
{
	char			*prompt;
	t_list			*pipeline_lst;
	t_list			*pid_lst;
	struct termios	term;
	struct termios	my_term;
	t_list			*env_lst;
	t_cap			cap;
	pid_t			lastpid;
	int				len_lst;
	t_exec			exec;
	int				fd_next[2];
	int				sig;
	int				status;
}					t_shell;

typedef struct s_variable
{
	char	*name;
	char	*value;
	int		flags;
}			t_var;

typedef struct s_path
{
	char	*env;
	char	*dir;
	char	*exe;
}			t_path;

typedef struct s_pid
{
	int		child;
}			t_pid;

typedef struct s_pos
{
	int		i;
	int		j;
}			t_pos;

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

/*		environ			*/

void	init_envlst(t_shell *sh, char **env);
int		add_var(t_var *var, t_list **env_lst);
int		build_var(char **str, t_list **env_lst, int (*f)());
int		cmp_var(t_var *var1, t_var *var2);
int		env_name_cmp(void *name, void *var);
t_list	*extract_env(char **env);
void	extract_var(char **str, char **name, char **value);
void	free_var(void *var);
char	*get_env(char *name, t_list *env_lst);
int		increase_shlvl(char *str, t_var *var);
int		init_var(char *name, char *value, t_list **env_lst);
int		is_env(t_var *var);
int		is_export(t_var *var);
char	*join_env(t_var *var);
int		modify_value(char *value, t_var *var);
void	restore_env(char **env);
void	set_flag(t_var *var, int flags);
void	set_flags(t_var *var);
int		set_var(char *name, char *value, t_list **env_lst, int (*f)());

/*		builtin			*/

int		execute_builtin(t_shell *sh, t_exec *exec);
int		check_builtin(int argc, char *arg);
int		check_builtin2(t_shell *sh, int argc, char **argv);
int		builtin_export(t_shell *sh, int argc, char **argv);
int		builtin_exit(t_shell *sh, int argc, char **argv);
int		builtin_cd(t_shell *sh, int argc, char **argv);
int		builtin_unset(t_shell *sh, int argc, char **argv);
int		builtin_env(t_list *var_lst);
int		builtin_pwd(t_shell *sh);
int		builtin_echo(t_shell *sh, char **argv);
int		is_valid_var(char *str);
void	print_builtin_error(t_shell *sh, char **argv, char *str, int status);
void	print_identifier_error(t_shell *sh, char *cmd, char *arg, int status);

/*		quoted			*/

void	args_have_quotes(t_list *lst, t_shell *sh);
int		redir_file_have_quotes(char **str, t_shell *sh);
void	change_content(t_list *lst, void *content);
char	*trim_quotes(char *str, t_shell *sh);
void	copy_without_quotes(char *dst, char *src, t_shell *sh);
void	copy_expander(char *dst, char *src, t_pos *pos, t_shell *sh);
void	copy_env(char *dst, char *name, int *j, t_shell *sh);
int		count_without_quotes(char *str, t_shell *sh);
int		count_expander(char *str, int *i, int *counter, t_shell *sh);
char	*get_env_name(char *str, int *i);
int		count_env(char *name, t_shell *sh);
void	is_quoted_2(char c, int *quoted, int *i);
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
t_token	*new_token(char *str);
int		id_token(char *str);
void	free_token(void *tkn);
void	del_current_token(t_list **tkn_lst);

/*		executer		*/

int		execute_pipeline(t_shell *sh, t_list *cmd_lst);
void	executer(t_shell *sh);
int		build_exec(t_exec *exec, t_cmd *cmd, t_shell *sh);
void	free_exec(t_exec *exec);
int		check_error(t_shell *sh, t_exec *exec);
int		set_redir(t_shell *sh, t_list *redir_lst);
int		wait_children(int *ret, int *sig);
int		execute_fork(t_shell *sh, int fd_in, int *fd_next, t_cmd *cmd);
void	reset_std_fd(int *fd);
void	cpy_std_fd(int *fd);
void	set_std_fd(int fd, int std);
int		print_error(t_shell *sh, char *str, char *msg, int status);
int		is_not_empty(char *str);
int		is_directory(char *path);
int		search_directory(char *path, char *name);
char	*get_exe_path(char *name, t_shell *sh);

/*		main			*/

void	init_keyboard(t_shell *sh);
void	init_environ(t_cap *cap);
void	print_prompt(char *prompt);
char	*read_command_line(t_shell *sh);
void	read_eval_print_loop(t_shell *sh);

#endif
