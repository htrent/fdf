/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:41:03 by htrent            #+#    #+#             */
/*   Updated: 2019/09/10 20:32:40 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_of_words(const char *str, char c, int *a)
{
	int		i;

	i = 0;
	*a = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str != c)
			if (*(str + 1) == c || *(str + 1) == '\0')
				i++;
		str++;
	}
	return (i);
}

static int		*length_of_words(const char *str, char c)
{
	int	*len;
	int	n;
	int	i;
	int	count;

	n = count_of_words(str, c, &count);
	i = 0;
	len = (int *)malloc(sizeof(int) * n);
	if (!len || !str || *str == '\0')
		return (NULL);
	while (i < n && *str)
	{
		while (*str == c)
			str++;
		count++;
		str++;
		if (*str == c || *str == '\0')
		{
			len[i++] = count;
			count = 0;
		}
	}
	return (len);
}

static int		check_split(char **split, const char *str)
{
	if (*str == '\0')
	{
		split[0] = 0;
		return (0);
	}
	return (1);
}

static	char	**write_split(const char *str, int *len, char **split, char c)
{
	int i;
	int j;
	int n;

	n = count_of_words(str, c, &i);
	j = 0;
	while (i < n)
	{
		split[i] = ft_strnew(len[i] + 1);
		if (!split[i])
			return (NULL);
		while (j < len[i])
			if (*str != c)
				split[i][j++] = *(str++);
			else
				str++;
		j = 0;
		i++;
	}
	split[n] = NULL;
	return (split);
}

char			**ft_strsplit(const char *str, char c)
{
	int		*len;
	int		i;
	char	**split;
	int		n;

	n = count_of_words(str, c, &i);
	len = length_of_words(str, c);
	split = (char **)malloc(sizeof(char*) * (n + 1));
	if (!split || !len || !check_split(split, str))
	{
		free(len);
		return (split);
	}
	split = write_split(str, len, split, c);
	if (split == NULL)
		while (split[i])
			free(split[i++]);
	free(len);
	return (split);
}
