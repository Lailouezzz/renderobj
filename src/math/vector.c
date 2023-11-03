/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:16:17 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/03 15:37:14 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file vector.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The vector implementation.
 * @date 2023-11-03
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

#include <math.h>

#include "math/vector.h"

// ************************************************************************** //
// *                                                                        * //
// * Function implementation                                                * //
// *                                                                        * //
// ************************************************************************** //

t_vec3f	vec_vec3add(
			const t_vec3f *a,
			const t_vec3f *b
			)
{
	return ((t_vec3f){a->x + b->x, a->y + b->y, a->z + b->z});
}

t_vec3f	vec_vec3sub(
			const t_vec3f *a,
			const t_vec3f *b
			)
{
	return ((t_vec3f){a->x - b->x, a->y - b->y, a->z - b->z});
}

t_vec3f	vec_vec3mul(
			const t_vec3f *a,
			GLfloat f
			)
{
	return ((t_vec3f){a->x * f, a->y * f, a->z * f});
}

t_vec4f	vec_vec3tvec4(
			const t_vec3f *vec,
			GLfloat w
			)
{
	return ((t_vec4f){vec->x, vec->y, vec->z, w});
}

GLfloat	vec_vec3length(
			const t_vec3f *vec
			)
{
	return ((GLfloat)
		sqrtf((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}

t_vec3f	vec_vec3normalize(
			const t_vec3f *vec
			)
{
	GLfloat	len;

	len = vec_vec3length(vec);
	return ((t_vec3f){vec->x / len, vec->y / len, vec->z / len});
}

t_vec3f	vec_vec4tvec3(
			const t_vec4f *vec
			)
{
	return ((t_vec3f){vec->x / vec->w, vec->y / vec->w, vec->z / vec->w});
}

t_vec3f	vec_vec3invert(
			const t_vec3f *vec
			)
{
	return ((t_vec3f){-vec->x, -vec->y, -vec->z});
}
