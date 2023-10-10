#include "../include/minishell.h"

void	ms_error(int size, ...);

void	ms_leaks()
{
	system("leaks -q minishell");
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
