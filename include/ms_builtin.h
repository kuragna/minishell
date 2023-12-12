/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:39:21 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/12 12:37:41 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTIN_H
# define MS_BUILTIN_H

# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../include/ms_malloc.h"
# include "./minishell.h"

# define MS_SIZE	7
# define MS_NVID	"not a valid identifier"
# define MS_NAR		"numeric argument required"

typedef int	(*t_fp)(t_data *);

typedef struct s_builtin
{
	const char	*name;
	t_fp		run;
}	t_builtin;

// int		ms_echo(int *fd);
// int		ms_pwd(int *fd);
// int		ms_cd(int *fd);
// int		ms_unset(int *fd);
// int		ms_export(int *fd);
// int		ms_env(int *fd);
// int		ms_exit(int *fd);

int		ms_echo(t_data *data);
int		ms_pwd(t_data *data);
int		ms_cd(t_data *data);
int		ms_unset(t_data *data);
int		ms_export(t_data *data);
int		ms_env(t_data *data);
int		ms_exit(t_data *data);

t_array	ms_env_dup(char **envp);
int		ms_start(int c);
int		ms_symbol(char *str, int c);
int		ms_get_idx(t_array *env, const char *name);
int		ms_env_push(t_array *env, char *var);
char	**ms_env_sort(char **envp);
char	*ms_getenv(t_array *env, const char *name);
void	ms_update_shlvl(t_array *env);
void	ms_export_print(t_array env, int *fd);

#endif // MS_BUILTIN_H
