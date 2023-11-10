#include "../../include/minishell.h"
#include <assert.h>

static int	ms_set_pwd(t_env *env, char *name, int pos)
{
	if (!name)
		return (1);
	if (pos == -1)
		return (ms_error("cd: %s not set\n"));
	free(env->vars[pos]);
	env->vars[pos] = name;
	return (0);
}

// TODO: simplify this function

int	ms_cd(t_env *env, char *path)
{
	char *go;
	size_t	len;

	if (!env->vars)
		return (1);
	go = path;
	len = ft_strlen(path);
	if (!path)
	{
		go = ms_getenv(env, "HOME");
		if (!go)
			return ms_error ("cd: HOME not set\n");
	}
	else if (ft_strncmp(path, "-", len) == 0 || ft_strncmp(path, "--", len) == 0)
	{
		go = ms_getenv(env, "OLDPWD");
		if (!go)
			return (ms_error("cd: OLDPWD not set\n"));
	}
	else if (ft_strncmp(path, "~", 1) == 0 || ft_strncmp(path, "~/", 2) == 0)
	{
		go = ms_getenv(env, "HOME");
		go = ft_strjoin(go, path + 1);
		if (!go)
			return (ms_error("cd: HOME not set\n"));
	}
	if (chdir(go) == -1)
		return (ms_error("cd: %s: %s\n", path, strerror(errno)));
	// NOTE: dont remove equal for strjoin
	go = ms_getenv(env, "PWD");
	ms_set_pwd(env, ft_strjoin("OLDPWD=", go), ms_get_idx(env, "OLDPWD"));
	ms_set_pwd(env, ft_strjoin("PWD=", getcwd(NULL, 0)), ms_get_idx(env, "PWD"));
	return (0);
}
