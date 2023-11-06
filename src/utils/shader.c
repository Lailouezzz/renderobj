/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:05:25 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/06 02:37:14 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file shader.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Shader utils implementation.
 * @date 2023-11-04
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils/shader.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper function prototypes                                             * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Write the compile error to STDERR, free the shader.
 * @param s The shader.
 */
static void	_compileshader_error(
				GLuint s
				);

// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

GLuint	shader_compile(
			char *data,
			size_t size,
			GLenum type
			)
{
	GLuint	s;
	GLint	st;
	char	*str;

	s = glCreateShader(type);
	if (s == 0)
		return (0);
	str = malloc(size + 1);
	if (str == NULL)
	{
		glDeleteShader(s);
		return (0);
	}
	memcpy(str, data, size);
	str[size] = '\0';
	glShaderSource(s, 1, (const char **)&str, NULL);
	glCompileShader(s);
	glGetShaderiv(s, GL_COMPILE_STATUS, &st);
	if (st == GL_FALSE)
	{
		_compileshader_error(s);
		s = 0;
	}
	free(str);
	return (s);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function                                                        * //
// *                                                                        * //
// ************************************************************************** //

static void	_compileshader_error(GLuint s)
{
	GLsizei	errlen;
	GLchar	errstr[1024];

	glGetShaderInfoLog(s, sizeof(errstr), &errlen, errstr);
	fprintf(stderr, "Shader compile error: %s", errstr);
	glDeleteShader(s);
}
