/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:02:44 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/21 10:21:04 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file shader.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Shader utils definition.
 * @date 2023-11-04
 * @copyright Copyright (c) 2023
 */

#ifndef  SHADER_H
# define SHADER_H

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

# include <GL/glew.h>

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes                                                    * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Compile shader source.
 * @param data The shader source.
 * @param size The shader source size.
 * @param type The shader type.
 * @return GLuint the shader id. 0 if error and write error to STDERR.
 */
GLuint	shader_compile(
			char *data,
			size_t size,
			GLenum type
			);

/**
 * @brief Link shader into a program
 * @param verts The vertex shader.
 * @param frags The frag shader.
 * @return GLuint the program id. 0 if error and write error to STDERR.
 */
GLuint	shader_link(
			GLuint verts,
			GLuint frags
			);

#endif
