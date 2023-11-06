/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:36:49 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/06 02:42:54 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file list.c
 * @author your name (you@domain.com)
 * @brief The implementation of a dynamic list.
 * @date 2023-11-06
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

#include <stdlib.h>
#include <string.h>

#include "utils/list.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

int	list_init(
			t_list *l,
			size_t elemsize
			)
{
	l->elemsize = elemsize;
	l->used = 0;
	l->alloced = 1;
	l->data = malloc(sizeof(l->elemsize) * l->alloced);
	return (l->data == NULL);
}

size_t	list_len(
			const t_list *l
			)
{
	return (l->used);
}

int	list_pushback(
		t_list *l,
		void *elem
		)
{
	if (l->used >= l->alloced)
	{
		l->data = realloc(l->data, l->elemsize * l->alloced * 2);
		if (l->data == NULL)
			return (1);
		l->alloced *= 2;
	}
	memcpy((char *)l->data + (l->elemsize * l->used++), elem, l->elemsize);
	return (0);
}
