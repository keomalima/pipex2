/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:39:27 by kricci-d          #+#    #+#             */
/*   Updated: 2025/01/07 16:33:23 by kricci-d         ###   ########.fr       */
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

static int	tab_len(char const *s, char c)
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

static	void	free_tab(char **tab, int index)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (index > i)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

static char	*get_str(const char **s, char c)
{
	int			str_len;
	char		*str;
	int			in_quotes;
	const char	*start;

	str_len = 0;
	start = *s;
	in_quotes = 0;
	while (**s && !is_delimiter(**s, c, &in_quotes))
		if (*(*s)++ != '\'' && *start != '"')
			str_len++;
	str = malloc(sizeof(char) * str_len + 1);
	if (!str)
		return (NULL);
	str_len = 0;
	while (start < *s)
	{
		if (*start != '\'' && *start != '"')
			str[str_len++] = *start;
		start++;
	}
	str[str_len] = '\0';
	return (str);
}

char	**ft_pipex_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		words;
	int		in_quotes;

	if (!s)
		return (NULL);
	in_quotes = 0;
	words = tab_len(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s && is_delimiter(*s, c, &in_quotes))
			s++;
		tab[i] = get_str(&s, c);
		if (!tab[i])
			return (free_tab(tab, i), NULL);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
