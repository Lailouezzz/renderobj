/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:50:26 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/05 01:39:05 by ale-boud         ###   ########.fr       */
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
 * @param rvec The #s_vec3f store the result.
 * @param a Vector a.
 * @param b Vector b.
 * @return #s_vec3f return rvec.
 */
t_vec3f	*vec_vec3add(
			t_vec3f *rvec,
			const t_vec3f *a,
			const t_vec3f *b
			);

/**
 * @brief Vector substraction (a.x - b.x, a.y - b.y, a.z - b.z).
 * @param rvec The #s_vec3f store the result.
 * @param a Vector a.
 * @param b Vector b.
 * @return #s_vec3f return rvec.
 */
t_vec3f	*vec_vec3sub(
			t_vec3f *rvec,
			const t_vec3f *a,
			const t_vec3f *b
			);

/**
 * @brief Vector scalar multiplication (a.x * f, a.y * f, a.z * f).
 * @param rvec The #s_vec3f store the result.
 * @param a Vector a.
 * @param f Factor f.
 * @return #s_vec3f return rvec.
 */
t_vec3f	*vec_vec3mul(
			t_vec3f *rvec,
			const t_vec3f *a,
			GLfloat f
			);

/**
 * @brief Convert a #s_vec3f to a #s_vec4f.
 * @param rvec The #s_vec4f store the result.
 * @param vec The #s_vec3f.
 * @param w The component w.
 * @return #s_vec4f return rvec.
 */
t_vec4f	*vec_vec3tvec4(
			t_vec4f *rvec,
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
 * @param rvec The #s_vec3f store the result.
 * @param vec The #s_vec3f.
 * @return #s_vec3f return rvec.
 */
t_vec3f	*vec_vec3normalize(
			t_vec3f *rvec,
			const t_vec3f *vec
			);

/**
 * @brief Convert a homegenous #s_vec4f to a #s_vec3f. (x/w, y/w, z/w).
 * @param rvec The #s_vec3f store the result.
 * @param vec The #s_vec4f.
 * @return #s_vec3f return rvec.
 */
t_vec3f	*vec_vec4tvec3(
			t_vec3f *rvec,
			const t_vec4f *vec
			);

/**
 * @brief Invert the #s_vec3f. (-vec.x, -vec.y, -vec.x).
 * @param rvec The #s_vec3f store the result.
 * @param vec The #s_vec3f.
 * @return #s_vec3f return rvec.
 */
t_vec3f	*vec_vec3invert(
			t_vec3f *rvec,
			const t_vec3f *vec
			);

/**
 * @brief Perform a cross product of vec1 x vec2.
 * @param rvec The #s_vec3f store the result.
 * @param vec1 The #s_vec3f.
 * @param vec2 The #s_vec3f.
 * @return #s_vec3f return rvec.
 */
t_vec3f	*vec_vec3cross(
			t_vec3f *rvec,
			const t_vec3f *vec1,
			const t_vec3f *vec2
			);

/**
 * @brief Perform a dot product of vec1 . vec2.
 * @param vec1 The #s_vec3f.
 * @param vec2 The #s_vec3f.
 * @return GLfloat The result.
 */
GLfloat	vec_vec3dot(
			const t_vec3f *vec1,
			const t_vec3f *vec2
			);

#endif
