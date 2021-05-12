#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int		work_to_list(t_env *_env, char *cmd);
char	*find_node(char *str, t_lista *lst);
void	set_export(int argc, char **cmdline, t_env *_env);
int		execute_builtin(int argc, char **cmdline, t_env *_env);
void	add_node_front(t_lista **lst, char *str);
void	add_node_before_last(t_lista *lst, char **str);
int		ft_delete_node(t_lista *lst, char **str);
t_list	*modify_value(t_list *list, char *value);

#endif