# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}


void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_ptr;
	char	*src_ptr;
	size_t	i;

	if (dest == NULL || src == NULL)
		return (NULL);
	i = -1;
	dest_ptr = (char *)dest;
	src_ptr = (char *)src;
	while (++i < n)
		dest_ptr[i] = src_ptr[i];
	return (dest);
}



int main (int argc, char **argv)
{
    char *str ="bonjour";
    char *str2 = "dieriba";
    printf("%s\n", ft_strjoin(str, str2, " lms"));
}