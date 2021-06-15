#ifndef ENV_H
# define ENV_H
//# include "minishell.h"
# define NL_KEY 10
# define DL_KEY 127
# define CTRL_D 4
# define CTRL_C 3
# define TAB 9
# define ESC 27
# define FALSE 0
# define TRUE 1

typedef struct s_line
{
	char	*origin_line;
	char	*clone_line;
}			t_line;

typedef struct s_lista
{
	void			*content;
	struct s_lista	*next;
	struct s_lista	*prev;
}	t_lista;

typedef struct s_environment
{
	char		str;
	int			check_esc;
	char		ch[4];
	int			index_ch;
	char		*cmd_line;
	t_lista		*cli;
	char		cmd_buff[2048];
	char		*cmd_cursor;
	int			cli_bufflen;
	int			len_cursor;
}	t_cap;

void	error_malloc(void);
int		capture(t_cap *cap, char **env);
int		search_var_name(void *str, void *var);
int		*read_cmdline(char **cmd, t_cap *cap);
int		ft_putchar(int c);
int		ft_insert_node_ini(t_lista **lst, t_lista *new);
int		ft_insert_nodo_fin(t_lista **lst, t_lista *new);
int		cap_key_printable(t_cap *cap);
int		cap_key_left(t_cap *cap);
int		cap_key_right(t_cap *cap);
int		cap_key_up(t_cap *cap);
int		cap_key_down(t_cap *cap);
int		cap_control(t_cap *cap, char **cmd);
char	**var_to_array(t_lista *lista);
void	find_history(t_cap *cap);
int		set_env(t_lista *lst, char *name, char *new_value);
void	cap_delete_char(t_cap *cap);
void	free_array(char **str);
void	free_node(t_lista *node);
void	create_empty_node(t_cap *cap);
void	create_node(t_cap *cap);
void	create_clon_node(t_cap *cap);
char	*next_line_key(t_cap *cap);
t_lista	*ft_dlstnew(void *content);
void	imprimir_content(void *cabeza);
int		imprimir_tabla(char **array);
void	imprimir_lista(t_lista *cabeza);

#endif
