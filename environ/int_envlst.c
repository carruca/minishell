#include "../minishell.h"

void	int_envlst(t_shell *sh, char **env)
{
	char	pwd[2048];	

	sh->env_lst = extract_env(env);
	set_var("TERM", "xterm-256color", &sh->env_lst, NULL);
	set_var("OLDPWD", NULL, &sh->env_lst, NULL);
	set_var("PWD", getcwd(pwd, sizeof(char) * 2048), &sh->env_lst, modify_value);
	set_var("SHLVL", "1", &sh->env_lst, increase_shlvl);
}
