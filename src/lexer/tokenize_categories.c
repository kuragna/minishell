#include "../../include/minishell.h"

void token_categorization(t_token **token)
{
	t_token *temp;
	temp = *token;
	while (temp->list && temp->list->next != NULL)
	{
		printf("content| %s\n", (char *)temp->list->content);
		if (!ft_strcmp(temp->list->content, ">>"))
			temp->token_type = "delimitor";	
		else if (!ft_strcmp(temp->list->content, "<<"))
			temp->token_type = "delimitor";	
		else if (!ft_strcmp(temp->list->content, ">>"))
			temp->token_type = "delimitor";
		else if (ms_is_metachar(*(char *)temp->list->content) == 1)
			temp->token_type = "delimitor";
		else
			temp->token_type = "word";
		temp->list = temp->list->next;
	}
	temp = *token;
}

#if 0 

int main()
{
	t_lexer lex; 
	t_token *token;

	while (1)
	{
		ft_memset(&lex, 0, sizeof(lex));
		lex.line = readline("$> ");
		ms_exit(lex.line);
		add_history(lex.line);
		token = split_line(&lex);
		token_categorization(&token);
		while (token && token->list != NULL)
		{
			printf("\ncontent = [%s]\n", (char *)token->list->content);
			printf("\ntype = [%s]\n", token->token_type);
			token->list = token->list->next;
		}
	}	
	return (0);
}

#endif
