#include "../include/ms_mem.h"

t_mem ms_mem_init(void)
{
	t_mem mem;

	mem.capacity = 8;
	mem.lenght = 0;
	mem.ptr = malloc(sizeof(void *) * mem.capacity); // TODO: check error
	return mem;
}
void	ms_mem_add(t_mem *mem, void *ptr)
{
	if (mem->capacity == mem->lenght)
	{
		ms_mem_realloc(mem);
	}
	mem->ptr[mem->lenght] = ptr;
	mem->lenght += 1;
}

void	ms_mem_realloc(t_mem *mem)
{
	void	**new;
	size_t	i;

	i = 0;
	mem->capacity *= 2;
	new = malloc(sizeof(void *) * mem->capacity); // check error
	while (i < mem->lenght)
	{
		new[i] = mem->ptr[i];
		i += 1;
	}
	free(mem->ptr);
	mem->ptr = new;
}

void	ms_mem_destroy(t_mem *mem)
{
	size_t i;

	i = 0;
	while (i < mem->lenght)
	{
		free(mem->ptr[i]);
		mem->ptr[i] = NULL;
		i += 1;
	}
	free(mem->ptr);
	mem->ptr = NULL;
}
