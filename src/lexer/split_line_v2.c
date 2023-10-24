/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_v2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:29:19 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/24 13:41:54 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Delimiters are | >> > < " '
 * first split with delimiters
 * then single quotes and double quotes
 * then spaces
 */

/**creating a modified split to split a line by all delimiters
 * 1) we move along the line looking for spaces once we encounter a space we take the starting position and the i - 1 pos and create a substring and then listaddback
 * 2) if we encounter a quote (be it a single or double quote) we enter in quote mode:
 * 			we are looking for the next identical quote to create our token however once we encounter it, we do not close the word until we encounter a space
 * 			then same thing => substring => listaddback
 * 3) at the end we will have a list of tokens, some will be words, some will be delimiters but we don't know this yet
 * 4) here we will go through our list of tokens and mark the tokens that are delimiters as delim_tokens
 * 5) do the expansions if needed
 * 6) we will look at the list and now determine what are the word types: cmd, args or file
 * 7) apply the function tolower to all cmd nodes through lstmap to be able execute commands in caps
 * 8) I think that's it :) ..................for now,..mmmm
 * -----------------------------------------------------------------------------------
 * */

//typedef struct s_lexer {
	//char	*result;
	//char	*temp;
	//int		flag;
	//size_t 	start;
	//size_t	end;
//}			t_lexer;


/*
 * New idea for parsing
 * what we keep:
 * - we are going through the line looking for spaces, onced encountered we take the starting pos and i -1 pos and create a substring and listaddback
 *   if we encounter a quote (single or double) we enter in quote mode:
 *   	we are looking for the next identical quote to create our token
 * DIFF:
 * 		once we encounter the other quote we substring from start to i -1 and redo the loop, we will join all the strings together until we find a space 
*/


void single_quote_mode(t_lexer *lex)
{
	size_t len = 0;
	size_t start = lex->pos;

	while (start < lex->len && lex->line[start] != SINGLE_QUOTE)
	{
		start += 1;
		len += 1;
	}
	if (lex->flag == 1)
	{
		//free(lex->result);	
		lex->temp = ft_strdup(lex->result);
	}
	lex->result = ft_substr(&lex->line[lex->pos], 0, len);
	lex->pos += len;
	printf("lex->result = %s\n", lex->result);
	if (lex->temp)
		lex->result = ft_strjoin(lex->temp, lex->result);
	while (lex->pos < lex->len || lex->line[lex->pos] != SPACE)
	{
		if (lex->line[lex->pos] == SINGLE_QUOTE)
		{
			lex->flag = 1;
			lex->start = lex->pos;
			lex->line += lex->pos;
			single_quote_mode(lex);
		}
		lex->pos++;
	}
}

//typedef struct

// '"test"'
// ^    ^
//

//void double_quote_mode(char *str, t_lexer *lex)
//{

//}
//
//A
//


typedef struct s_string
{
	char	*str;
	size_t	length;
	size_t	capacity;
} t_string;


void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return NULL;
	ft_memcpy(new, ptr, size);
	free(ptr);
	return new;
}

void	append(t_string *string, char c)
{
	if (string->length == string->capacity)
	{
		string->capacity *= 2;
		string->str = ft_realloc(string->str, string->capacity * sizeof(char));
	}
	string->str[string->length] = c;
	string->length += 1;
}

t_string string_init()
{
	t_string string;
	
	string.capacity = 8;
	string.length = 0;
	string.str = malloc(string.capacity);
	return string;
}

void skip_quotes(t_lexer *lex, char c)
{
	if (lex->line[lex->pos] == c && lex->line[lex->pos + 1] == c)
		lex->pos += 2;
}

int	main()
{
	t_string string = string_init();

	char *line = readline("$> ");

	while (*line)
	{
		if (*line != SINGLE_QUOTE || *line != DOUBLE_QUOTE)
			append(&string, *line);
		line += 1;
	}
	append(&string, '\0');

	printf("[line]: %s\n", string.str);

	return 0;
}

//void add_char(t_lexer *lex, char c)
//{
	//size_t	len_res;

	//len_res = ft_strlen(lex->result);
	////if (lex->result)
		////free(lex->result);
	//lex->result = malloc(1 * (len * 2) + 1);


//}

int ft_isprint_no_quotes(char c)
{
	if (c > 32 && c < 127 && c != SINGLE_QUOTE && c != DOUBLE_QUOTE)
		return (1);
	return (0);
}	

void normal_mode(t_lexer *lex)
{
	while (ft_isprint_no_quotes(lex->line[lex->pos]))
		lex->pos++;
	if (lex->line[lex->pos] != SINGLE_QUOTE && lex->line[lex->pos] != DOUBLE_QUOTE && lex->line[lex->pos] == SPACE)
		lex->result = ft_substr(lex->line, lex->start, lex->pos - lex->start);
}

void create_token(t_lexer *lex)
{
	t_token	*token;

	token = NULL;
	token = malloc(sizeof(t_token));
	ft_memset(token, 0, sizeof(*token));

	while (lex->pos < lex->len)
	{
		if (lex->line[lex->pos] == SINGLE_QUOTE)
			single_quote_mode(lex);
		else
			normal_mode(lex);
			
		//else if (str[lex->pos] == DOUBLE_QUOTE)
			//double_quote_mode(str, lex);
		lex->pos++;
	}	
}


#if 0

int main()
{
	char	*str;
	t_lexer	lex;

	ft_memset(&lex, 0, sizeof(t_lexer));
	while (1)
	{
		str = readline("$> ");
		lex.len = ft_strlen(str);
		lex.line = str;
		ms_exit(str);
		add_history(str);
		create_token(&lex);
	}
	return (0);
	//printf("%d\n", delimiters_present(str));
}

#endif

/*
">>" asd

>">" asd
/bin/rm -f ">"

>> '$USER'
cat $USER
/bin/rm -f '$USER'

>> '$USER'
cat '$USER'
/bin/rm -f '$USER'

"echo "

"echo -nnnnn"

"ECho" -n -nnn"" "-"nnnnn

"ECHO" "-n"

ECHO '''''-''n'

echo '' -n

echo "" "" "" -n -n -n -n

cat << $USER
why
not
$USER

export T=">>"
$T lol

cat << "$USER"
why
not
$USER

cat << "$US"E"R"
because
we
love
bash
$USER

>> $HOME

>> "$H"OM"E"
cat OME
/bin/rm -f OME

>> "$USER'$USER'"
cat "$USER'$USER'"
/bin/rm -f "$USER'$USER'"

>> "$USER"
cat $USER
/bin/rm -f $USER

cd /Users/$USER/Desktop/
pwd

cd /Users/"$USER"/Desktop/
pwd

cd /Users/"$U"S"ER"/Desktop/

export T=n
echo "-"$T$T

export T=ech
echo $To

export T=ech
echo $T"o"

export T=ech
echo $T"o "

export T=ech
echo $T"o -n"

export T=ech
echo $T"o -n"

export T=ech
echo $T'o'

export T="-n test1 -n test 2"
echo $T

export T=ech
echo $T'o '

"ECHO"

'echo'

'PWD'

"PWD"

echo "-nnnnn "

ECHO -nn

ECHO -n -n

ECHO "-"""n""n""n""n""n""nnnnnn-n

ECHO "-"""n""n""n""n""n""nnnnnn -n

export T=nnnnnnnn
echo "-""$T"nnnnnnnnnnnnn -nnnnnnnn"$T" '-'"$T"

export T=nnnnnnnn
echo "-""$T"nnnnnnnnnnnnn -nnnnnnnn"$T" '-''$T'

export T=nnnnnnnn
echo "-"'$T'nnnnnnnnnnnnn -nnnnnnnn'$T' '-'"$T "

export T=nnnnnnnn
echo "-"'$T'nnnnnnnnnnnnn -nnnnnnnn$T '-''$T '

export T=e E=c S=h L=o
$T$E$S$L

export T=e E=c S=h L=o L=ok
$T$E$S$L

export T=e E=c S=h L=o
$T$E$S$L -n

export T=E E=c S=h L=o
$T$E$S$L -n

export T=E E=c S=h L=o
$T$E$S$L -nn

export T=e E=c S=h L=o
$T$E$S$L -nn

export T=e E=c S=h L=o
$T$E"c"$L -nn

export T=e E=c S=h L=o
$T$E"C"$L -nn

export T=e E=c S=h L=o
$T$E"C"$L "" -""n

LS

Ls

lS

ls

PWD

pWD

pwd

pwD

ENV

CAT

EXPORT

export T="|"
echo segfault $T grep segfault

export T='|'
echo segfault $T grep segfault

export T=">"
echo segfault $T grep segfault

export T='<'
echo segfault $T grep segfault

export T="<<"
echo segfault $T grep segfault

export T='<<'
echo segfault $T grep segfault

export T="|"
$T$T$T$T$T$T$T

export T="echo segfault | grep segfault"
$T

export T=-nnnnnnnn"nnnnnnn "
echo $T

export T=-"n                    "
Echo $T

EXIT 123

Exit

UNSET USER

Unset USER

EXPORT T=LA
echo $T

Export T=LA
echo $T

"e"'x''p''o''r''t' L=T
echo $T

e""""""""""""cho

export T='|'
echo $T echo lala $T echo $T echo ?

export T="<<"
$T.

OLDPWD

USER

" ls"

" cat"

" echo"

" PWD"

" pwd"

"PWD "

"pwd "

'pwd '

p""''''w''''''""""""''''''''''''''''''''''''''''''''d

'''''''''''''''' echo ok

           ''echo ok

           ""echo ok

           ""echo"" ok

           ""'echo'"" ok

echo "         |       "  | echo maybe

echo "|"  | echo maybe

echo '|'  | echo maybe

echo -nnnnnnnnnnnn

export L=amazing L=ok L=cool
echo $L

export L=amazing L=ok L=cool
export L=ok
echo $L

echo '$'$'$'$'$'

echo '$'$'$'$'$'$'$'

echo "$"$'$'$"$"$"$"$'$'

echo $/ $/ 

echo $U/SER

echo "$/ $/"

echo $/"$/"

echo '$/'

exit 9223372036854775805

exit 123"123"

<| echo ok

>| echo sure

cd --
 */

