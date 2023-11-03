/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:00:10 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/03 17:03:04 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file vb.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The fixed size vertex buffer implementation.
 * @date 2023-11-03
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

#include <stdlib.h>

#include "buffer/vb.h"

// ************************************************************************** //
// *                                                                        * //
// * Function implementation                                                * //
// *                                                                        * //
// ************************************************************************** //

t_vb	*vb_init(
			size_t size
			)
{
	t_vb	*vb;

	vb = malloc(sizeof(*vb));
	if (vb == NULL)
		return (NULL);
	vb->vertices = malloc(sizeof(*vb->vertices) * size);
	if (vb->vertices == NULL)
	{
		free(vb);
		return (NULL);
	}
	vb->size = size;
	return (vb);
}

void	vb_destroy(
			t_vb *vb
			)
{
	if (vb != NULL)
	{
		if (vb->vertices != NULL)
			free(vb->vertices);
		free(vb);
	}
}
