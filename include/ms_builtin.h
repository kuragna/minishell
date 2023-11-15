#ifndef MS_BUILTIN_H
#define MS_BUILTIN_H

#include <stdlib.h>
#include "../libft/libft.h"
#include "../include/ms_malloc.h"
#include "./minishell.h"

#define MS_STDOUT	1

int		ms_env(t_array env);
int		ms_echo(char **args, int *fd);
int		ms_pwd(void);
int		ms_cd(t_array *env, char *path);
int     ms_unset(t_array *env, char **args);
int     ms_export(t_array *env, char **vars);
void    ms_exit();



int		ms_export_(t_array *env, char *var);
int     ms_start(int c);
int     ms_symbol(char *str, int c);
int		ms_get_idx(t_array *env, const char *name);
char	*ms_getenv(t_array *env, char *name);

t_array ms_env_dup(char **envp);
int		ms_env_push(t_array *env, char *var);
void	ms_env_sort(t_array env);



#endif // MS_BUILTIN_H
