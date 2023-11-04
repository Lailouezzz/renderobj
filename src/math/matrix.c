/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:18:38 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/04 13:12:59 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file matrix.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The matrix implementation.
 * @date 2023-11-03
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

#include "math/matrix.h"

t_mat4	*mat_mat4empty(
			t_mat4 *m
			)
{
	*m = (t_mat4){{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
	return (m);
}

t_mat4	*mat_mat4ident(
			t_mat4 *m
			)
{
	mat_mat4empty(m);
	m->x[0] = 1.;
	m->y[1] = 1.;
	m->z[2] = 1.;
	m->w[3] = 1.;
	return (m);
}

t_mat4	*mat_mat4xmat4(
			t_mat4 *mat1,
			const t_mat4 *mat2
			)
{
	int		k;
	t_mat4	rmat;

	k = 0;
	while (k < 4)
	{
		rmat.x[k] = mat1->x[0] * mat2->x[k] + mat1->x[1] * mat2->y[k]
			+ mat1->x[2] * mat2->z[k] + mat1->x[3] * mat2->w[k];
		rmat.y[k] = mat1->y[0] * mat2->x[k] + mat1->y[1] * mat2->y[k]
			+ mat1->y[2] * mat2->z[k] + mat1->y[3] * mat2->w[k];
		rmat.z[k] = mat1->z[0] * mat2->x[k] + mat1->z[1] * mat2->y[k]
			+ mat1->z[2] * mat2->z[k] + mat1->z[3] * mat2->w[k];
		rmat.w[k] = mat1->w[0] * mat2->x[k] + mat1->w[1] * mat2->y[k]
			+ mat1->w[2] * mat2->z[k] + mat1->w[3] * mat2->w[k];
		++k;
	}
	*mat1 = rmat;
	return (mat1);
}

t_vec4f	*mat_mat4xvec4(
			t_vec4f *rvec,
			const t_mat4 *mat,
			const t_vec4f *vec
			)
{
	rvec->x = mat->x[0] * vec->x + mat->x[1] * vec->y
		+ mat->x[2] * vec->z + mat->x[3] * vec->w;
	rvec->y = mat->y[0] * vec->x + mat->y[1] * vec->y
		+ mat->y[2] * vec->z + mat->y[3] * vec->w;
	rvec->z = mat->z[0] * vec->x + mat->z[1] * vec->y
		+ mat->z[2] * vec->z + mat->z[3] * vec->w;
	rvec->w = mat->w[0] * vec->x + mat->w[1] * vec->y
		+ mat->w[2] * vec->z + mat->w[3] * vec->w;
	return (rvec);
}

t_mat4	*mat_transmat4(
			t_mat4 *rmat,
			const t_vec3f *vec
			)
{
	mat_mat4ident(rmat);
	rmat->x[3] = vec->x;
	rmat->y[3] = vec->y;
	rmat->z[3] = vec->z;
	return (rmat);
}
