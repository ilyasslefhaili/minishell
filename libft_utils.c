/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:56:06 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/06 13:33:51 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
int ft_strlen(char *s)
{
	int count;
	count = 0;
	while (*s++)
		count++;
	return (count);
}
char	*ft_substr(char *s, int start, int len)
{
	char			*sub_s;
	int			sub_index;
	int	i;

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
char	*ft_strcpy(char *dst,  char *src)
{
	char	*saved;

	saved = dst;
	while (*src)
	{
		*dst++ = *src++;
	}
	*dst = '\0';
	return (saved);
}

char	*ft_strcat(char *dst,  char *src)
{
	size_t	dst_len;
	char	*string;

	dst_len = ft_strlen (dst);
	string = dst + dst_len;
	while (*src)
	{
		*string++ = *src++;
	}
	*string = '\0';
	return (dst);
}

char	*ft_strjoin(char  *s1, char  *s2)
{
	char	*string;

	if (!s1)
		return (NULL);
	string = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!string)
		return (NULL);
	ft_strcpy (string, s1);
	ft_strcat (string, s2);
	return (string);
}