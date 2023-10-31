#include "../../include/minishell.h"

int	ms_cd(t_env *env, char *path)
{
	char *go;
	size_t	len;
	
	// TODO: replace go by path
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
		return 1;
	char	*a = ft_strjoin("OLDPWD=", go);
	char	*b = ft_strjoin("PWD=", getcwd(NULL, 0));
	go = ms_getenv(env, "PWD=");
	ms_export(env, &a);
	ms_export(env, &b);
	return 0;
}

