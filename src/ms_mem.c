#include "../include/ms_mem.h"
#include <string.h>


#if 0
t_mem ms_mem_init(void)
{
	t_mem mem;

	mem.capacity = 8;
	mem.length = 0;
	mem.ptr = malloc(sizeof(void *) * mem.capacity); // TODO: check error
	return mem;
}

void	ms_mem_add(t_mem *mem, void *ptr)
{
	if (mem->capacity == mem->length)
	{
		mem->capacity *= 2;
		mem->ptr = ft_realloc(mem->ptr, sizeof(char *) * mem->capacity);
	}
	mem->ptr[mem->length] = ptr;
	mem->length += 1;
}


void	ms_mem_destroy(t_mem *mem)
{
	size_t i;

	i = 0;
	while (i < mem->length)
	{
		free(mem->ptr[i]);
		mem->ptr[i] = NULL;
		i += 1;
	}
	free(mem->ptr);
	mem->ptr = NULL;
}


void	leaks()
{
	system("leaks -q main");
}

int	main()
{
	atexit(leaks);
	t_mem mem;
	memset(&mem, 0, sizeof(t_mem));

	char	*str = strdup("test");
	char	*s   = strdup("test2");



	ft_lstadd_front(&mem.lst, ft_lstnew(str));
	mem.len += 1;
// 	ft_lstadd_front(&mem.lst, ft_lstnew(s));
// 	mem.len += 1;
	return 0;
}
#endif









