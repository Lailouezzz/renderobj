/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:46:35 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/07 16:37:50 by ale-boud         ###   ########.fr       */
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

// ************************************************************************** //
// *                                                                        * //
// * Struct definition                                                      * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @todo Doc
 */
typedef enum e_uniform_id {
	UNIFORM_MVP,
	UNIFORM__COUNT
}	t_uniform_id;

/**
 * @todo Doc
 */
typedef struct s_uniforms {
	GLint	programid;
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
int	uniform_init(
		t_uniforms *uniforms,
		GLint programid
		);

#endif
