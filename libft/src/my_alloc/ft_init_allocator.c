/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_allocator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:11:50 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/17 21:36:09 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_my_alloc.h"

t_lalloc	*ft_init_allocator(void)
{
	t_lalloc	*new;
	t_my_malloc	*allocator_node;

	new = malloc(sizeof(t_lalloc));
	if (!new)
		return (NULL);
	allocator_node = malloc(sizeof(t_my_malloc));
	if (!allocator_node)
	{
		free(new);
		return (NULL);
	}
	allocator_node->size = sizeof(t_lalloc);
	allocator_node->ptr = new;
	allocator_node->next = NULL;
	new->head = allocator_node;
	new->total_allocated = sizeof(t_lalloc);
	new->total_freed = 0;
	return (new);
}
