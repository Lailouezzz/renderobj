/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:49:30 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/16 18:23:31 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file matrix.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The matrix definition.
 * @date 2023-11-03
 * @copyright Copyright (c) 2023
 */

#ifndef  MATRIX_H
# define MATRIX_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include <GL/glew.h>

# include "math/vector.h"

// ************************************************************************** //
// *                                                                        * //
// * Struct definition                                                      * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @struct s_mat4
 * @brief Matrix 4x4.
 */
typedef struct s_mat4 {
	GLfloat	x0;
	GLfloat	y0;
	GLfloat	z0;
	GLfloat	w0;
	GLfloat	x1;
	GLfloat	y1;
	GLfloat	z1;
	GLfloat	w1;
	GLfloat	x2;
	GLfloat	y2;
	GLfloat	z2;
	GLfloat	w2;
	GLfloat	x3;
	GLfloat	y3;
	GLfloat	z3;
	GLfloat	w3;
}	t_mat4;

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes                                                    * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Set the #s_mat4 to an empty matrix.
 * @param m The #s_mat4
 * @return Pointer to m.
 */
t_mat4	*mat_mat4empty(
			t_mat4 *m
			);

/**
 * @brief Set the #s_mat4 to an identity matrix.
 * @param m The #s_mat4
 * @return Pointer to m.
 */
t_mat4	*mat_mat4ident(
			t_mat4 *m
			);

/**
 * @brief Perform a matrix matrix product (mat1 * mat2).
 * @param rmat #s_mat4 store the result.
 * @param mat1 #s_mat4 the mat1.
 * @param mat2 #s_mat4 the mat2.
 * @return Pointer to rmat.
 */
t_mat4	*mat_mat4xmat4(
			t_mat4 *rmat,
			const t_mat4 *mat1,
			const t_mat4 *mat2
			);

/**
 * @brief Perform a vector matrix multiplication (mat * vec).
 * @param rvec #s_vec3f store the result.
 * @param mat #s_mat4 the mat.
 * @param vec #s_vec3f the vec.
 * @return Pointer to rvec.
 */
t_vec4f	*mat_mat4xvec4(
			t_vec4f *rvec,
			const t_mat4 *mat,
			const t_vec4f *vec
			);

/**
 * @brief Produce a translate matrix.
 * @param rmat #s_mat4 store the result.
 * @param vec #s_vec3f the vec for the translation.
 * @return Pointer to rmat.
 */
t_mat4	*mat_transmat4(
			t_mat4 *rmat,
			const t_vec3f *vec
			);

/**
 * @brief Produce a scale matrix.
 * @param rmat #s_mat4 store the result.
 * @param vec #s_vec3f the vec for the scaling. (1, 1, 1) * mat = rmat
 * @return Pointer to rmat.
 */
t_mat4	*mat_scalemat4(
			t_mat4 *rmat,
			const t_vec3f *vec
			);

/**
 * @brief Produce a scale matrix.
 * @param rmat #s_mat4 store the result.
 * @param vec #s_vec3f the vec for the scaling. (1, 1, 1) * mat = rmat
 * @return Pointer to rmat.
 */
t_mat4	*mat_lookatmat4(
			t_mat4 *rmat,
			const t_vec3f *pos,
			const t_vec3f *look,
			const t_vec3f *up
			);

/**
 * @brief Produce a perspective projection perspective.
 * @param rmat #s_mat4 store the result.
 * @param fov FOV in degree.
 * @param width width of buffer.
 * @param height height of buffer.
 * @return Pointer to rmat.
 */
t_mat4	*mat_projperspmat4(
			t_mat4 *rmat,
			GLfloat fov,
			int width,
			int height
			);

#endif
