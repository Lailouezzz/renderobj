/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:18:38 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/21 00:55:01 by ale-boud         ###   ########.fr       */
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
	*m = (t_mat4){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	return (m);
}

t_mat4	*mat_mat4ident(
			t_mat4 *m
			)
{
	*m = (t_mat4){
		1., 0., 0., 0.,
		0., 1., 0., 0.,
		0., 0., 1., 0.,
		0., 0., 0., 1.
	};
	return (m);
}

t_mat4	*mat_mat4xmat4(
			t_mat4 *rmat,
			const t_mat4 *mat1,
			const t_mat4 *mat2
			)
{
	int		k;
	t_mat4	tmat;

	k = 0;
	while (k < 4)
	{
		(&tmat.x0)[k * 4]
			= mat1->x0 * (&mat2->x0)[k * 4] + mat1->x1 * (&mat2->y0)[k * 4]
			+ mat1->x2 * (&mat2->z0)[k * 4] + mat1->x3 * (&mat2->w0)[k * 4];
		(&tmat.y0)[k * 4]
			= mat1->y0 * (&mat2->x0)[k * 4] + mat1->y1 * (&mat2->y0)[k * 4]
			+ mat1->y2 * (&mat2->z0)[k * 4] + mat1->y3 * (&mat2->w0)[k * 4];
		(&tmat.z0)[k * 4]
			= mat1->z0 * (&mat2->x0)[k * 4] + mat1->z1 * (&mat2->y0)[k * 4]
			+ mat1->z2 * (&mat2->z0)[k * 4] + mat1->z3 * (&mat2->w0)[k * 4];
		(&tmat.w0)[k * 4]
			= mat1->w0 * (&mat2->x0)[k * 4] + mat1->w1 * (&mat2->y0)[k * 4]
			+ mat1->w2 * (&mat2->z0)[k * 4] + mat1->w3 * (&mat2->w0)[k * 4];
		++k;
	}
	*rmat = tmat;
	return (rmat);
}

t_vec4f	*mat_mat4xvec4(
			t_vec4f *rvec,
			const t_mat4 *mat,
			const t_vec4f *vec
			)
{
	rvec->x = mat->x0 * vec->x + mat->x1 * vec->y
		+ mat->x2 * vec->z + mat->x3 * vec->w;
	rvec->y = mat->y0 * vec->x + mat->y1 * vec->y
		+ mat->y2 * vec->z + mat->y3 * vec->w;
	rvec->z = mat->z0 * vec->x + mat->z1 * vec->y
		+ mat->z2 * vec->z + mat->z3 * vec->w;
	rvec->w = mat->w0 * vec->x + mat->w1 * vec->y
		+ mat->w2 * vec->z + mat->w3 * vec->w;
	return (rvec);
}

t_mat4	*mat_transmat4(
			t_mat4 *rmat,
			const t_vec3f *vec
			)
{
	mat_mat4ident(rmat);
	rmat->x3 = vec->x;
	rmat->y3 = vec->y;
	rmat->z3 = vec->z;
	return (rmat);
}

t_mat4	*mat_scalemat4(
			t_mat4 *rmat,
			const t_vec3f *vec
			)
{
	mat_mat4ident(rmat);
	rmat->x0 = vec->x;
	rmat->y1 = vec->y;
	rmat->z2 = vec->z;
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
		xaxis.x, yaxis.x, zaxis.x, 0.,
		xaxis.y, yaxis.y, zaxis.y, 0.,
		xaxis.z, yaxis.z, zaxis.z, 0.,
		-vec_vec3dot(pos, &xaxis),
		-vec_vec3dot(pos, &yaxis),
		-vec_vec3dot(pos, &zaxis),
		1.
	};
	return (rmat);
}

#define FAR 1000.
#define NEAR 0.01

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
	rmat->x0 = -e / ar;
	rmat->y1 = e;
	rmat->z2 = (GLfloat)(FAR + NEAR) / (FAR - NEAR);
	rmat->z3 = -(GLfloat)(2. * FAR * NEAR) / (FAR - NEAR);
	rmat->w2 = 1.;
	return (rmat);
}
