
#include "stdlib.h"
#include "stdio.h"
int	valid_double_split(char const *s, size_t i)
{
	if ((i > 0 && s[i - 1] != '\\') || i == 0)
		return (1);
	return (0);
}

void	skip_split(char *to_parse, size_t *i, int quote)
{
	size_t	j;

	j = (*i);
    printf("Entered at index : %ld string is : %s\n", j, &to_parse[j]);
	while (1)
	{
		while (to_parse[++j])
		{
			if ((to_parse[j] == quote && to_parse[j] == '"')
				&& valid_double_split(to_parse, j))
				break ;
			else if (to_parse[j] == quote && to_parse[j] != '"')
            {
                printf("Out at index : %ld string is : %s\n", j, to_parse);
				break ;
            }
		}
        if (to_parse[j] == 0)
            break ;
		else if (to_parse[j + 1] == '\'' || to_parse[j + 1] == '"')
			quote = to_parse[++j];
	}
	(*i) = j;
}


size_t	find_next_separator(char *to_parse, size_t i, char c)
{
	while (to_parse[i])
	{
		if ((to_parse[i] == '"' && valid_double_split(to_parse, i))
			|| to_parse[i] == '\'')
			skip_split(to_parse, &i, to_parse[i]);
		else if (to_parse[i] == c)
			break ;
		i++;
	}
	return (--i);
}

int	find_end_word(char *s, char c, size_t k)
{
	while (s[k] && s[k] != c)
	{
		if ((s[k] == '"' && valid_double_split(s, k)) || s[k] == '\'')
			skip_split(s, &k, s[k]);
		k++;
	}
	return (k);
}

int	free_all_tab_split(char **tab, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free(tab[i]);
	free(tab);
	return (1);
}


static int	ft_tablen(char *s, char c)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			len++;
		i = find_next_separator(s, i, c);
		i++;
	}
	return (len);
}

static int	fill_tab(char **tab, char *s, char c, int len)
{
	int	i;
	int	j;
	int	k;
	int	m;

	i = 0;
	j = 0;
	while (i < len)
	{
		while (s[j] && s[j] == c)
			j++;
		k = j;
		k = find_end_word(s, c, k);
		tab[i] = calloc(sizeof(char), (k - j + 1));
		if (!tab[i])
			return (free_all_tab_split(tab, i));
		m = 0;
		while (j < k)
			tab[i][m++] = s[j++];
		i++;
	}
	return (0);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		len;

	if (!s)
		return (NULL);
	len = ft_tablen((char *)s, c);
	tab = calloc(sizeof(char *), (len + 1));
	if (!tab)
		return (NULL);
	if (fill_tab(tab, s, c, len))
		return (NULL);
	return (tab);
}

int main (int argc, char **argv)
{
    char **tab = ft_split("git commit -m 'protection added'", '\n');
}