/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:39:27 by kricci-d          #+#    #+#             */
/*   Updated: 2025/01/13 07:52:26 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	is_delimiter(char c, char delimiter, int *in_quotes)
{
	if ((c == '\'' || c == '"') && (*in_quotes == 0))
		*in_quotes = 1;
	else if ((c == '\'' || c == '"') && (*in_quotes == 1))
		*in_quotes = 0;
	return (c == delimiter && *in_quotes == 0);
}

static	int	tab_len(char const *s, char c)
{
	int	count;
	int	in_quotes;

	count = 0;
	in_quotes = 0;
	while (*s)
	{
		while (*s && is_delimiter(*s, c, &in_quotes))
			s++;
		if (*s && !is_delimiter(*s, c, &in_quotes))
		{
			count++;
			while (*s && !is_delimiter(*s, c, &in_quotes))
				s++;
		}
	}
	return (count);
}

static char	*extract_str(const char *start, const char *end)
{
	char	*str;
	int		str_len;

	str_len = 0;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	while (start < end)
	{
		if (*start != '\'' && *start != '"')
			str[str_len++] = *start;
		else if (*(start + 1) == *start)
		{
			str[str_len++] = '\0';
			start++;
		}
		start++;
	}
	str[str_len] = '\0';
	return (str);
}

static char	*get_str(const char **s, char c)
{
	const char	*start;
	int			in_quotes;

	in_quotes = 0;
	while (**s && is_delimiter(**s, c, &in_quotes))
		(*s)++;
	start = *s;
	in_quotes = 0;
	while (**s && !is_delimiter(**s, c, &in_quotes))
		(*s)++;
	return (extract_str(start, *s));
}

char	**ft_pipex_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		words;

	if (!s)
		return (NULL);
	words = tab_len(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < words)
	{
		tab[i] = get_str(&s, c);
		if (!tab[i])
			return (free_nsplit(tab, i), NULL);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
