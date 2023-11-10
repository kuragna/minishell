#ifndef MS_MEM
#define MS_MEM

#include <stdlib.h>
#include "../libft/libft.h"

// typedef struct s_mem
// {
// 	t_list *lst;
// 	size_t	len;
// } t_mem;

typedef struct s_mem
{
	void	**ptr;
	size_t	capacity;
	size_t	length;
} t_mem;

t_mem	ms_mem_init(void);
void	ms_mem_add(t_mem *mem, void *ptr);
void	ms_mem_realloc(t_mem *mem);
void	ms_mem_destroy(t_mem *mem);


#endif // MS_MEM

