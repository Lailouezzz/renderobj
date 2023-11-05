/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:16:17 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/05 01:43:10 by ale-boud         ###   ########.fr       */
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

t_vec3f	*vec_vec3add(
			t_vec3f *rvec,
			const t_vec3f *a,
			const t_vec3f *b
			)
{
	*rvec = ((t_vec3f){a->x + b->x, a->y + b->y, a->z + b->z});
	return (rvec);
}

t_vec3f	*vec_vec3sub(
			t_vec3f *rvec,
			const t_vec3f *a,
			const t_vec3f *b
			)
{
	*rvec = ((t_vec3f){a->x - b->x, a->y - b->y, a->z - b->z});
	return (rvec);
}

t_vec3f	*vec_vec3mul(
			t_vec3f *rvec,
			const t_vec3f *a,
			GLfloat f
			)
{
	*rvec = ((t_vec3f){a->x * f, a->y * f, a->z * f});
	return (rvec);
}

t_vec4f	*vec_vec3tvec4(
			t_vec4f *rvec,
			const t_vec3f *vec,
			GLfloat w
			)
{
	*rvec = ((t_vec4f){vec->x, vec->y, vec->z, w});
	return (rvec);
}

GLfloat	vec_vec3length(
			const t_vec3f *vec
			)
{
	return ((GLfloat)
		sqrtf((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}

t_vec3f	*vec_vec3normalize(
			t_vec3f *rvec,
			const t_vec3f *vec
			)
{
	GLfloat	len;

	len = vec_vec3length(vec);
	*rvec = ((t_vec3f){vec->x / len, vec->y / len, vec->z / len});
	return (rvec);
}

t_vec3f	*vec_vec4tvec3(
			t_vec3f *rvec,
			const t_vec4f *vec
			)
{
	*rvec = ((t_vec3f){vec->x / vec->w, vec->y / vec->w, vec->z / vec->w});
	return (rvec);
}

t_vec3f	*vec_vec3cross(
			t_vec3f *rvec,
			const t_vec3f *vec1,
			const t_vec3f *vec2
			)
{
	*rvec = ((t_vec3f){vec1->y * vec2->z - vec1->z * vec2->y,
			vec1->z * vec2->x - vec1->x * vec2->z,
			vec1->x * vec2->y - vec1->y * vec2->x});
	return (rvec);
}

GLfloat	vec_vec3dot(
			const t_vec3f *vec1,
			const t_vec3f *vec2
			)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}
