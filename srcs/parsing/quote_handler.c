
#include "../../includes/minishell.h"

int	skip_quotes(const char *str, int i, char quote)
{
	int	len;

	len = 1;
	i++;
	while (str[i] && str[i] != quote)
	{
		len++;
		i++;
	}
	if (str[i] == quote)
		len++;
	return (len);
}

static int	copy_until_quote(char *dst, const char *src, int *j, char q)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != q)
		dst[(*j)++] = src[i++];
	if (src[i] == q)
		i++;
	return (i);
}

static char	*build_unquoted(const char *src)
{
	char	*dst;
	int		i;
	int		j;

	dst = malloc(ft_strlen(src) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '"')
			i += copy_until_quote(dst, &src[i + 1], &j, src[i]);
		else
			dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return (dst);
}

char	*remove_quotes(char *str)
{
	char	*new;

	if (!str)
		return (NULL);
	new = build_unquoted(str);
	free(str);
	return (new);
}

int	has_unclosed_quote(const char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] != quote)
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}
