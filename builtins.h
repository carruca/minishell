#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

char	*find_node(char *str, t_lista *lst);
int 	set_export(int argc, char **cmdline, t_cap *cap);
int		execute_builtin(int argc, char **cmdline, t_cap *cap);
void	add_node_front(t_lista **lst, char *str);
void	add_node_before_last(t_lista *lst, char **str);
int		ft_delete_node(t_lista *lst, char **str);
t_list	*modify_value(t_list *list, char *value);

#endif