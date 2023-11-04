/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:50:26 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/04 13:08:31 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file vector.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The vector definition.
 * @date 2023-11-03
 * @copyright Copyright (c) 2023
 */

#ifndef  VECTOR_H
# define VECTOR_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include <GL/glew.h>

// ************************************************************************** //
// *                                                                        * //
// * Structure definition                                                   * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @struct s_vec4f
 * @brief Vector 4.
 */
typedef struct __attribute__((packed)) s_vec4f
{
	GLfloat	x;
	GLfloat	y;
	GLfloat	z;
	GLfloat	w;
}	t_vec4f;

/**
 * @struct s_vec3f
 * @brief Vector 3.
 */
typedef struct __attribute__((packed)) s_vec3f
{
	GLfloat	x;
	GLfloat	y;
	GLfloat	z;
}	t_vec3f;

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes                                                    * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Vector addition (a.x + b.x, a.y + b.y, a.z + b.z).
 * @param a Vector a.
 * @param b Vector b.
 * @return #s_vec3f result of the vector addition.
 */
t_vec3f	vec_vec3add(
			const t_vec3f *a,
			const t_vec3f *b
			);

/**
 * @brief Vector substraction (a.x - b.x, a.y - b.y, a.z - b.z).
 * @param a Vector a.
 * @param b Vector b.
 * @return #s_vec3f result of the vector substraction.
 */
t_vec3f	vec_vec3sub(
			const t_vec3f *a,
			const t_vec3f *b
			);

/**
 * @brief Vector scalar multiplication (a.x * f, a.y * f, a.z * f).
 * @param a Vector a.
 * @param f Factor f.
 * @return #s_vec3f result of the vector multiplication.
 */
t_vec3f	vec_vec3mul(
			const t_vec3f *a,
			GLfloat f
			);

/**
 * @brief Convert a #s_vec3f to a #s_vec4f.
 * @param vec The #s_vec3f.
 * @param w The component w.
 * @return #s_vec4f The converted #s_vec3f.
 */
t_vec4f	vec_vec3tvec4(
			const t_vec3f *vec,
			GLfloat w
			);

/**
 * @brief The length of a vector 3.
 * @param vec The #s_vec3f.
 * @return GLfloat The length.
 */
GLfloat	vec_vec3length(
			const t_vec3f *vec
			);

/**
 * @brief Normalize a vector 3.
 * @param vec The #s_vec3f.
 * @return #s_vec3f The normalized vector. 
 */
t_vec3f	vec_vec3normalize(
			const t_vec3f *vec
			);

/**
 * @brief Convert a homegenous #s_vec4f to a #s_vec3f.
 * @param vec The #s_vec4f.
 * @return #s_vec3f The converted #s_vec4f. (x/w, y/w, z/w).
 */
t_vec3f	vec_vec4tvec3(
			const t_vec4f *vec
			);

/**
 * @brief Invert the #s_vec3f.
 * @param vec The #s_vec3f.
 * @return #s_vec3f The inverted #s_vec3f. (-vec.x, -vec.y, -vec.x).
 */
t_vec3f	vec_vec3invert(
			const t_vec3f *vec
			);

#endif
