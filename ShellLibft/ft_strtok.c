/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:37:54 by vagarcia          #+#    #+#             */
/*   Updated: 2025/02/11 12:33:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*skip_delimiters(char *str, const char *delim)
{
	int j;

	while (*str)
	{
		j = 0;
		while (delim[j])
		{
			if (*str == delim[j])
				break ;
			j++;
		}
		if (!delim[j])
			return (str);
		str++;
	}
	return (NULL);
}

static char	*find_token_end(char *str, const char *delim)
{
	int j;

	while (*str)
	{
		j = 0;
		while (delim[j])
		{
			if (*str == delim[j])
			{
				*str = '\0';
				return (str + 1);
			}
			j++;
		}
		str++;
	}
	return (NULL);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*saved_str;
	char		*token;

	if (str)
		saved_str = str;
	if (!saved_str)
		return (NULL);
	saved_str = skip_delimiters(saved_str, delim);
	if (!saved_str)
		return (NULL);
	token = saved_str;
	saved_str = find_token_end(saved_str, delim);
	return (token);
}