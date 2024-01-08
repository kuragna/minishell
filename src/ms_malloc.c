//#include "../include/ms_malloc.h"
#include <stdio.h>
#include <stdlib.h>

void	*ms_malloc(size_t size, char *file, int line)
{
	void	*p = (malloc)(size);
	fprintf(stderr, "%s:%d -> `%p`\n", file, line, p);
	return p;
}
