/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:05:25 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/07 15:44:14 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file shader.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Shader implementation.
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

#include "render/shader.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper function prototypes                                             * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Write the compile error to STDERR, free the shader.
 * @param s The shaderid.
 */
static void	_shader_compile_error(
				GLuint s
				);

/**
 * @brief Write the link error to STDERR, free the program.
 * @param p The programid.
 */
static void	_shader_link_error(
				GLuint p
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
		_shader_compile_error(s);
		s = 0;
	}
	free(str);
	return (s);
}

GLuint	shader_link(
			GLuint verts,
			GLuint frags
			)
{
	GLuint	programid;
	GLint	st;

	programid = glCreateProgram();
	if (programid == 0)
		return (0);
	glAttachShader(programid, verts);
	glAttachShader(programid, frags);
	glLinkProgram(programid);
	glDetachShader(programid, verts);
	glDetachShader(programid, frags);
	glDeleteShader(verts);
	glDeleteShader(frags);
	glGetProgramiv(programid, GL_LINK_STATUS, &st);
	if (st == GL_FALSE)
	{
		_shader_link_error(programid);
		programid = 0;
	}
	return (programid);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function                                                        * //
// *                                                                        * //
// ************************************************************************** //

static void	_shader_compile_error(GLuint s)
{
	GLsizei	errlen;
	GLchar	errstr[1024];

	glGetShaderInfoLog(s, sizeof(errstr), &errlen, errstr);
	fprintf(stderr, "Shader compile error: %s", errstr);
	glDeleteShader(s);
}

static void	_shader_link_error(
				GLuint p
				)
{
	GLsizei	errlen;
	GLchar	errstr[1024];

	glGetProgramInfoLog(p, sizeof(errstr), &errlen, errstr);
	fprintf(stderr, "Shader compile error: %s", errstr);
	glDeleteProgram(p);
}
