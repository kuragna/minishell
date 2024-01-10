/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:29:43 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/09 19:33:19 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_lexer.h"

extern int	g_status;

static void	ms_heredoc_quote(t_lexer *l, struct s_string *word, char quote)
{
	while (l->pos < l->len && l->line[l->pos] != quote)
	{
		ms_char_append(word, l->line[l->pos]);
		l->pos += 1;
	}
	l->pos += 1;
}

char	*ms_heredoc_dlmtr(t_lexer *l, struct s_string *word)
{
	char	quote;

	while (l->pos < l->len && !ms_is_token(l->line[l->pos]))
	{
		if (ms_is_quote(l->line[l->pos]))
		{
			l->data.quotes_flag = 1;
			quote = l->line[l->pos];
			l->pos += 1;
			ms_heredoc_quote(l, word, quote);
		}
		if (l->pos >= l->len)
			break ;
		if (!ms_is_token(l->line[l->pos]))
			ms_char_append(word, l->line[l->pos]);
		l->pos += 1;
	}
	ms_char_append(word, '\0');
	return (word->data);
}

static void	ms_heredoc_exit_status(struct s_string *word)
{
	char	*status;

	status = ft_itoa(g_status);
	if (status)
	{
		ms_str_append(word, status);
		free(status);
	}
}

int	ms_heredoc_child(char *file_path, char *dlmtr, t_data *data)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == -1)
		return (ms_error("minishell: %s\n", strerror(errno)), -1);
	if (pid == 0)
	{
		signal(SIGINT, ms_heredoc_sig_handler);
		fd = ms_open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ms_heredoc(fd, dlmtr, data);
		close(fd);
		exit(0);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		if (WIFEXITED(g_status) && WEXITSTATUS(g_status) == 1)
		{
			data->heredoc_flag = 1;
			return (g_status = WEXITSTATUS(g_status), -1);
		}
	}
	return (ms_open(file_path, O_RDONLY, 0));
}

char	*ms_heredoc_expansion(char *name, t_data *data)
{
	struct s_string	word[2];

	word[0] = ms_string_init();
	word[1] = ms_string_init();
	while (word[0].data && word[1].data && name && *name)
	{
		if (*name == '$' && *(name + 1))
		{
			name += 1;
			if (*name == '?')
			{
				ms_heredoc_exit_status(&word[0]);
				name += 1;
			}
			while (*name && *name != '$' && ms_is_usalnum(*name))
				ms_char_append(&word[1], *name++);
			ms_char_append(&word[1], '\0');
			ms_str_append(&word[0], ms_getenv(data->env, word[1].data));
			word[1].len = 0;
		}
		if (*name)
			ms_char_append(&word[0], *name++);
	}
	return (free(word[1].data), ms_char_append(&word[0], '\0'), word[0].data);
}
