#ifndef MS_MEM
#define MS_MEM

#include <stdlib.h>

typedef struct s_mem
{
	void	**ptr;
	size_t	lenght;
	size_t	capacity;
} t_mem;

t_mem	ms_mem_init(void);
void	ms_mem_add(t_mem *mem, void *ptr);
void	ms_mem_realloc(t_mem *mem);
void	ms_mem_destroy(t_mem *mem);


#endif // MS_MEM

