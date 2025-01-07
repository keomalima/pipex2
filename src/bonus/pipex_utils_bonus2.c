/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:39:27 by kricci-d          #+#    #+#             */
/*   Updated: 2025/01/07 18:30:21 by keomalima        ###   ########.fr       */
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

static int calculate_token_length(const char **s, char c, int *in_quotes)
{
	int	str_len;

	str_len = 0;
	*in_quotes = 0;
	while (**s && !is_delimiter(**s, c, in_quotes))
	{
		if (**s != '\'' && **s != '"')
			str_len++;
		else if (*(*s + 1) == **s)
		{
			str_len++;
			(*s)++;
		}
		(*s)++;
	}
	return str_len;
}

static char *extract_token(const char *start, const char *end)
{
	char	*str;
	int		str_len;

	str_len = 0;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return NULL;
	while (start < end)
	{
		if (*start != '\'' && *start != '"')
			str[str_len++] = *start;
		else if (*(start + 1) == *start)
		{
			str[str_len++] = ' ';
			start++;
		}
	}
	start++;
	str[str_len] = '\0';
	return str;
}

// Main function: combines both parts
static char *get_str(const char **s, char c)
{
	const char	*start;
	int	in_quotes;
	int	str_len;

	in_quotes = 0;
	while (**s && is_delimiter(**s, c, &in_quotes))
		(*s)++;
	start = *s;
	str_len = calculate_token_length(s, c, &in_quotes);
	if (str_len == 0)
		return NULL;
	return extract_token(start, *s);
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
	while (*s && is_delimiter(*s, c, &in_quotes))
		s++;
	in_quotes = 0;
	while (**s && !is_delimiter(**s, c, &in_quotes))
	{
		if (**s != '\'' && **s != '"')
			str_len++;
		else
		{
			if ((*start) + 1 == '\'' || (*start) + 1 == '"')
				str_len++;
		}
		(*s)++;
	}
	str = malloc(sizeof(char) * str_len + 1);
	if (!str)
		return (NULL);
	str_len = 0;
	while (start < *s)
	{
		if (*start != '\'' && *start != '"')
			str[str_len++] = *start;
		else
		{
			if ((*start) + 1 == '\'' || (*start) + 1 == '"')
				str[str_len++] = ' ';
		}
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
			return (free_tab(tab, i), NULL);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
