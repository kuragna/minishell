/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:35:52 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/13 19:55:09 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LEXER_H
# define MS_LEXER_H


/* --------Structures Overview--------*/
typedef struct s_token t_token;


/* --------Structures Detailed--------*/
typedef struct s_token {
//	t_type token_type;
	t_list *list;
}				t_token;


/* -------------Functions-------------*/
t_token *split_line(char *line);

/* --------------Defines--------------*/
# define SPACE 32

#endif
