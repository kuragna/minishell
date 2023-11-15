#include "../include/minishell.h"

int ms_trim_left(t_lexer *l)
{
	while (l->pos < l->len && ft_isspace(l->line[l->pos]))
	{
		l->pos += 1;
	}
	return l->pos;
}

int	ms_is_token(int c)
{
	if (ft_isspace(c) || c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

int	ms_interactive_mode(void)
{
	struct termios attr;

	if (!isatty(MS_STDIN))
	{
		return (1);
	}
	if (tcgetattr(MS_STDIN, &attr) == -1)
	{
		return (1);
	}
	attr.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(MS_STDIN, TCSANOW, &attr) == -1)
	{
		return (1);
	}
	return (0);
}
