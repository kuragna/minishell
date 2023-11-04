#include "../../include/minishell.h"
#include <assert.h>

void	ms_set_pwd(t_env *env, char *name, size_t len)
{
	int	pos;

	pos = ms_get_idx(env, name, len);
	assert(pos != -1 && "position is -1 can't put it in array index");
	free(env->vars[pos]);
	env->vars[pos] = name;
}

int	ms_cd(t_env *env, char *path)
{
	char *go;
	size_t	len;
	
	go = path;
	len = ft_strlen(path);
	if (!path)
	{
		go = ms_getenv(env, "HOME=");
		if (go == NULL)
			return ms_error ("cd: HOME not set\n");
	}
	else if (ft_strncmp(path, "-", len) == 0 || ft_strncmp(path, "--", len) == 0)
	{
		go = ms_getenv(env, "OLDPWD=");
		if (go == NULL)
			ms_error("cd: OLDPWD not set\n");
	}
	else if ((*path == '~' && *(path + 1) == '\0') || (*path == '~' && *(path + 1) == '/'))
	{
		path += 1;
		go = ms_getenv(env, "HOME=");
		go = ft_strjoin(go, path);
		if (go == NULL)
			return ms_error("cd: HOME not set\n");
	}
	if (chdir(go) == -1)
	{
		return ms_error("cd: %s: %s\n", go, strerror(errno));
	}
	if (!env)
		return (1);
	go = ms_getenv(env, "PWD=");
	ms_set_pwd(env, ft_strjoin("OLDPWD=", go), 7);
	ms_set_pwd(env, ft_strjoin("PWD=", getcwd(NULL, 0)), 4);
	return (0);
}

