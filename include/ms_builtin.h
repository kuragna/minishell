#ifndef MS_BUILTIN_H
#define MS_BUILTIN_H

#include <stdlib.h>
#include "../libft/libft.h"
#include "../include/ms_malloc.h"

#define MS_STDOUT	1


// TODO: try to use hashtable

typedef struct s_env
{
    char	**vars;
	size_t	capacity;
	size_t	length;
} t_env;


int		ms_env(t_env env);
int		ms_echo(char **args, int *fd);
int		ms_pwd(void);
int		ms_cd(t_env *env, char *path);
int     ms_unset(t_env *env, char **args);
int     ms_export(t_env *env, char **vars);
void    ms_exit();



int		ms_export_(t_env *env, char *var);
int     ms_start(int c);
int     ms_symbol(char *str, int c);
int		ms_get_idx(t_env *env, const char *name);
char	*ms_getenv(t_env *env, char *name);

t_env   ms_env_dup(char **envp);
int		ms_env_push(t_env *env, char *var);
void	ms_env_sort(t_env env);



#endif // MS_BUILTIN_H
