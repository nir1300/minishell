/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:17:33 by vagarcia          #+#    #+#             */
/*   Updated: 2024/09/10 18:37:34 by vagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;

	len = 0;
	if (size > 0)
	{
		while (src[len] && len < (size - 1))
		{
			dest[len] = src[len];
			len++;
		}
		dest[len] = '\0';
	}
	while (src[len] != '\0')
		len++;
	return (len);
}
/*
#include <unistd.h>
#include <strings.h>
#include <stdio.h>
int main() {
    char const *src = "abcd5678";
    char *dest = "1234";
	size_t len1;

	len1 = ft_strlcpy(dest, src, sizeof(dest));
	//size_t len2;
	//len2 = strlcpy(dest, src, sizeof(dest));
    printf("%s\n", src);
    printf("%s\n", dest);
    printf("ft = %zu\n", len1);
	//printf("strlcpy = %zu\n", len2);

    return(0);
}*/
