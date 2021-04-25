#ifndef COMMAND_H
# define COMMAND_H

#include "executer.h"
#include "minishell.h"

int		search_directory(char *path, char *name);
char	*get_exe_path(char *name);
int		executer_command(char *path, char **argv);
void	print_command_error(char *cmd, char *prompt);

#endif
