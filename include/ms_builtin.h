#ifndef MS_BUILTIN_H
#define MS_BUILTIN_H

#include <stdlib.h>

// TODO: use another struct

typedef struct s_env
{
    char	**vars;
	size_t	capacity;
	size_t	length;
} t_env;


void    ms_env(t_env env);
// void	ms_echo(char *text);
void	ms_echo(char **args);
int		ms_pwd(void);
int		ms_cd(t_env *env, char *path);
int     ms_unset(t_env *env, char *name);
int     ms_export(t_env *env, char *var);
void    ms_exit(char *line);



int     ms_start(int c);
int     ms_symbol(char *str, int c);
// int		ms_get_idx(t_env *env, const char *name);
int		ms_get_idx(t_env *env, const char *name, size_t len);
char	*ms_getenv(t_env *env, char *name);

t_env   env_dup(char **envp);
void	env_add(t_env **env, char *var);
void	env_sort(t_env *env);
void	export_print(t_env *env);
size_t	env_size(char **envp);



#endif // MS_BUILTIN_H
