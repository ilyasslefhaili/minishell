/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:56:06 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/07 12:02:32 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "get_next_line.h"
char	*ft_substr(char *s, size_t start, size_t len)
{
	char			*sub_s;
	size_t			sub_index;
	size_t	i;

	if (!s)
		return (NULL);
	sub_index = 0;
	i = 0;
	if (start >= ft_strlen(s))
	{
        char *temp;
        temp = malloc(sizeof(char));
        temp[0] ='\0';
        return (temp);
    }
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	sub_s = (char *)malloc((len + 1) * sizeof(char));
	if (!sub_s)
		return (NULL);
	while (s[i])
	{
		if (i >= start && sub_index < len)
		{
			sub_s[sub_index++] = s[i];
		}
		i++;
	}
	sub_s[sub_index] = '\0';
	return (sub_s);
}
int	get_parts(char *s, char c)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (s[i])
	{
		if ((s[0] != c && i == 0) || (s[i] != c && s[i - 1] == c && s[i]))
			n++;
		i++;
	}
	return (n);
}
char	**ft_split(char *s, char c)
{
	int		index;
	char	**result;
	int		i;
	int		o;

	i = 0;
	if (!s)
		return (NULL);
	result = malloc((get_parts (s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	index = 0;
	while (index < get_parts (s, c))
	{
		while (s[i] == c && s[i])
			i++;
		o = i;
		while (s[i] != c && s[i])
			i++;
		result[index] = ft_substr(s, o, i - o);
		index++;
	}
	result[index] = NULL;
	return (result);
}