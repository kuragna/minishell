#include "../include/minishell.h"

int	ms_error(const char *fmt, ...)
{
	va_list ap;
	char	*str;

	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt += 1;
			if (*fmt == 's')
			{
				str = va_arg(ap, char *);
				ft_putstr_fd(str, MS_STDERR);
				fmt += 1;
			}
		}
		write(MS_STDERR, fmt, 1);
		fmt += 1;
	}
	va_end(ap);
	return (1);
}
