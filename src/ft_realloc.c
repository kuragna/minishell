void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	if (size == 0)
		return NULL;
	new = malloc(size);
	if (!new)
		return NULL;
	ft_memmove(new, ptr, size);
	free(ptr);
	return new;
}