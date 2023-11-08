/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:18:38 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/08 19:27:29 by ale-boud         ###   ########.fr       */
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

#include <math.h>

#include "math/matrix.h"

// ************************************************************************** //
// *                                                                        * //
// * Function header                                                        * //
// *                                                                        * //
// ************************************************************************** //

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
	*m = (t_mat4){
		{1., 0., 0., 0.},
		{0., 1., 0., 0.},
		{0., 0., 1., 0.},
		{0., 0., 0., 1.}
	};
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

t_mat4	*mat_scalemat4(
			t_mat4 *rmat,
			const t_vec3f *vec
			)
{
	mat_mat4ident(rmat);
	rmat->x[0] = vec->x;
	rmat->y[1] = vec->y;
	rmat->z[2] = vec->z;
	return (rmat);
}

t_mat4	*mat_lookatmat4(
			t_mat4 *rmat,
			const t_vec3f *pos,
			const t_vec3f *look,
			const t_vec3f *up
			)
{
	t_vec3f	xaxis;
	t_vec3f	yaxis;
	t_vec3f	zaxis;

	vec_vec3normalize(&zaxis, vec_vec3sub(&zaxis, look, pos));
	vec_vec3normalize(&xaxis, vec_vec3cross(&xaxis, up, &zaxis));
	vec_vec3cross(&yaxis, &zaxis, &xaxis);
	*rmat = (t_mat4){
	{xaxis.x, yaxis.x, zaxis.x, 0.},
	{xaxis.y, yaxis.y, zaxis.y, 0.},
	{xaxis.z, yaxis.z, zaxis.z, 0.},
	{vec_vec3dot(&xaxis, look), vec_vec3dot(&yaxis, look), vec_vec3dot(&zaxis, look), 1.}
	};
	return (rmat);
}

#define FEAR 1000
#define NEAR 0.1

t_mat4	*mat_projperspmat4(
			t_mat4 *rmat,
			GLfloat fov,
			int width,
			int height
			)
{
	const GLfloat	ar = (GLfloat)width / height;
	const GLfloat	e = 1. / tanf(fov / 2);

	mat_mat4empty(rmat);
	rmat->x[0] = e / ar;
	rmat->y[1] = e;
	rmat->z[2] = (GLfloat)(FEAR + NEAR) / (NEAR - FEAR);
	rmat->z[3] = (GLfloat)(2. * FEAR * NEAR) / (NEAR - FEAR);
	rmat->w[2] = -1.;
}
