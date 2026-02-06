/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:32:31 by maleca            #+#    #+#             */
/*   Updated: 2025/08/08 19:37:28 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*p;
	int		size;

	size = 0;
	if (!lst)
		return (0);
	p = lst;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}
