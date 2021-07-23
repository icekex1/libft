/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzeck <tzeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:40:16 by tzeck             #+#    #+#             */
/*   Updated: 2021/07/23 16:42:08 by tzeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
​
static int	delimiter(char to_check, char c)
{
	if (to_check == c || to_check == '\0')
		return (1);
	else
		return (0);
}
​
static int	string_count(char const *s, char c)
{
	int	i;
	int	words;
​
	i = 0;
	words = 0;
	while (s[i])
	{
		if (delimiter(s[i], c) == 0 && delimiter(s[i + 1], c) == 1)
			words++;
		i++;
	}
	return (words);
}
​
static int	free_array(char **arr, int arr_index)
{
	int	tmp;
​
	if (arr[arr_index] == NULL)
	{
		while (arr_index >= 0)
		{
			tmp = arr_index;
			free(arr[arr_index]);
			arr[arr_index] = NULL;
			arr_index = tmp - 1;
		}
		free (arr);
		arr = NULL;
		return (1);
	}
	return (0);
}
​
static int	write_words(char **arr, char const *s, char c)
{
	int	i;
	int	j;
	int	arr_index;
​
	i = 0;
	arr_index = 0;
	while (s[i])
	{
		while (delimiter(s[i], c) == 1 && s[i])
			i++;
		j = 0;
		while (delimiter(s[i + j], c) == 0 && s[i + j])
			j++;
		arr[arr_index] = (char *)malloc((j + 1) * sizeof(char));
		if (free_array(arr, arr_index) == 1)
			return (1);
		j = 0;
		while (delimiter(s[i], c) == 0 && s[i])
			arr[arr_index][j++] = s[i++];
		arr[arr_index][j] = '\0';
		if (delimiter(s[i - 1], c) == 0)
			arr_index++;
	}
	arr[arr_index] = NULL;
	return (0);
}
​
char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		b;
​
	if (s == NULL)
		return (NULL);
	arr = (char **)malloc((string_count(s, c) + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	b = write_words(arr, s, c);
	if (b == 1)
		return (NULL);
	return (arr);
}
