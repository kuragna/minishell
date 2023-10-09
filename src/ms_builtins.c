#include "../include/minishell.h"

void	ms_error(int size, ...);

void	ms_leaks()
{
	system("leaks -q minishell");
}

int ms_pwd(void)
{
	char	*path = getcwd(NULL, 0);
	if (path == NULL)
	{
		MS_ERROR("minishell: ", path, strerror(ENOENT));
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

#if 0
void	ms_error(int size, ...)
{
	va_list	ap;

	va_start(ap, size);
	for (int i = 0; i < size - 1; i++)
	{
		ft_putstr_fd(va_arg(ap, char *), 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(va_arg(ap, char *), 2);
	va_end(ap);
}
#endif

void	ms_echo(char *text)
{
	// TODO: handle trim space
	// TODO: fix strign if has quotes function printing newline
	// TODO: with option -n
	// TODO: trim space from right
	// TODO: handle multiplle strings
	
	size_t	i = 0;

	if (text && *text == MS_DOLLAR)
		text = getenv(text + 1);
	while (text && text[i])
	{
		if (text[i] == MS_SLASH)
			i += 1;
		printf("%c", text[i]);
		i += 1;
	}
	printf("\n");
}

int	ms_cd(const char *path)
{
	int err = chdir(path);
	if (err == -1)
	{
		MS_ERROR("cd: ", path, strerror(errno));
		return 1;
	}
	return 0;
}
