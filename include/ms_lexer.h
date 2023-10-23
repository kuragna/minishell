/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:35:52 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/23 17:05:36 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LEXER_H
# define MS_LEXER_H


/* --------Structures Overview--------*/
typedef struct s_token t_token;
typedef struct s_lexer t_lexer;


/* --------Structures Detailed--------*/
typedef struct s_token {
//	t_type token_type;
	t_list *list;
}				t_token;

typedef struct s_lexer {

	char	*line;
	char	*result;
	char	*temp;
	int		flag;
	size_t	len;
	size_t	start;
	size_t 	pos;
}				t_lexer;

// '''''test''''test
//              ^
// pos


/* -------------Functions-------------*/
t_token *split_line(char *line);
//int		single_quote_mode(t_token *token, char *line, size_t *start, size_t *end);
//int		double_quote_mode(t_token *token, char *line, size_t *start, size_t *end);

/* --------------Defines--------------*/
# define SPACE 32

#endif
