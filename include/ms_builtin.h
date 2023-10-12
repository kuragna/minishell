#ifndef MS_BUILTIN_H
#define MS_BUILTIN_H

#include <stdlib.h>

typedef struct s_env
{
    char	**vars;
	size_t	capacity;
	size_t	lenght;
} t_env;


void    ms_env(t_env env);
void	ms_echo(char *str);
int		ms_pwd(void);
int		ms_cd(t_env *env, char *path);
int     ms_unset(t_env *env, char *name);
int     ms_export(t_env *env, char *var);
void    ms_exit(char *line);



int     ms_start(int c);
int     ms_symbol(char *str, int c);
t_env   env_dup(char **envp);


#endif // MS_BUILTIN_H
