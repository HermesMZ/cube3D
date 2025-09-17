/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_strdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:26:27 by zoum              #+#    #+#             */
/*   Updated: 2025/09/17 21:28:29 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char	*ft_my_strdup(t_lalloc *allocator, const char *s)
{
	int		i;
	char	*temp;

	if (!s)
		return (NULL);
	temp = (char *)ft_my_malloc(allocator, sizeof(char) * (ft_strlen(s) + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (s[i])
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
