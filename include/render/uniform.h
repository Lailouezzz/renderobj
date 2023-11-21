/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:46:35 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/21 09:50:07 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file uniform.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The render definition.
 * @date 2023-11-07
 * @copyright Copyright (c) 2023
 */

#ifndef  UNIFORM_H
# define UNIFORM_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include <GL/glew.h>

# include "math/matrix.h"

// ************************************************************************** //
// *                                                                        * //
// * Struct definition                                                      * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @todo Doc
 */
typedef enum e_uniform_id {
	UNIFORM_VIEW,
	UNIFORM_PROJ,
	UNIFORM_ZMUL,
	UNIFORM__COUNT
}	t_uniform_id;

/**
 * @todo Doc
 */
typedef struct s_uniforms {
	GLuint	programid;
	GLint	uniforms[UNIFORM__COUNT];
}	t_uniforms;

// ************************************************************************** //
// *                                                                        * //
// * Function prototype                                                     * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Initialize the uniforms.
 * @param uniforms The #s_uniforms.
 * @param programid The programid.
 * @return int 0 if success. non-null value if error.
 */
int		uniform_init(
			t_uniforms *uniforms,
			GLuint programid
			);

/**
 * @brief Set the uniform.
 * @param uid The uniform id #s_uniform_id.
 * @param mat The matrix.
 */
void	uniform_setmat4(
			t_uniforms *uniforms,
			t_uniform_id uid,
			const t_mat4 *mat
			);

/**
 * @brief Set the uniform.
 * @param uid The uniform id #s_uniform_id.
 * @param n The float.
 */
void	uniform_setfloat(
			t_uniforms *uniforms,
			t_uniform_id uid,
			GLfloat n
			);

#endif
