#ifndef MS_MALLOC
#define MS_MALLOC

#include <stdlib.h>

#define malloc(size) ms_malloc(size, __FILE__, __LINE__)

void	*ms_malloc(size_t size, char *file, int line);

#endif //MS_MALLOC
