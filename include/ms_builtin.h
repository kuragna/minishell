/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:39:21 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/05 19:46:49 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTIN_H
# define MS_BUILTIN_H

# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../include/ms_malloc.h"
# include "./minishell.h"

# define MS_STDOUT	1
# define MS_SIZE 	7
# define MS_NVID "not a valid identifier"

extern struct s_context g_ctx;

typedef int	(*t_fp)(int *);

typedef struct s_builtin
{
	const char	*name;
	t_fp		run;
}	t_builtin;

int		ms_echo(int *fd);
int		ms_pwd(int *fd);
int		ms_cd(int *fd);
int		ms_unset(int *fd);
int		ms_export(int *fd);
int		ms_env(int *fd);
int		ms_exit(int *fd);

int		ms_start(int c);
int		ms_symbol(char *str, int c);
int		ms_get_idx(t_array *env, const char *name);
char	*ms_getenv(t_array *env, const char *name);
t_array	ms_env_dup(char **envp);
int		ms_env_push(t_array *env, char *var);
// void	ms_env_sort(t_array env);
char	**ms_env_sort(char **envp);
void	ms_update_shlvl(t_array *env);
void	ms_export_print(t_array env);

#endif // MS_BUILTIN_H
