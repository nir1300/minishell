/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vip_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagarcia <vagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:27:17 by vagarcia          #+#    #+#             */
/*   Updated: 2025/02/12 12:44:25 by vagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t copy_size;

	// If new_size is 0, free the memory and return NULL
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	// If ptr is NULL, treat it as a malloc
	if (ptr == NULL)
	{
		new_ptr = ft_calloc(new_size, sizeof(char));
		if (!new_ptr)
		{
			errno = ENOMEM; // Set errno to indicate out-of-memory
			return (NULL);
		}
		return (new_ptr);
	}
	new_ptr = ft_calloc(new_size, sizeof(char));
	if (!new_ptr)
	{
		errno = ENOMEM; // Set errno to indicate out-of-memory
		return (NULL);
	}
	if (old_size < new_size)
		copy_size = old_size;
	else
    copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	if (ptr)
		free(ptr);
	return (new_ptr);
}