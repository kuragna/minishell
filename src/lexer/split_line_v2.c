/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_v2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:29:19 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/20 18:54:58 by glacroix         ###   ########.fr       */
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

typedef struct s_lexer {
	char *input;
	char *result;
	size_t start;
	size_t end;
}			t_lexer;


char *create_token(char *input)
{
	
}


#if 1 

int main()
{
	char	*str;


	while (1)
	{
		str = readline("$> ");
		ms_exit(str);
		add_history(str);
		create_token(str);
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

