/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:05:25 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/16 18:29:21 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file uniform.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Uniform implementation.
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

#include "render/uniform.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper struct                                                          * //
// *                                                                        * //
// ************************************************************************** //

static const char	*g_uniforms_name[UNIFORM__COUNT] = {
[UNIFORM_MVP] = "mvp"
};

// ************************************************************************** //
// *                                                                        * //
// * Helper function prototypes                                             * //
// *                                                                        * //
// ************************************************************************** //

// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

int	uniform_init(
		t_uniforms *uniforms,
		GLuint programid
		)
{
	int	k;

	uniforms->programid = programid;
	k = 0;
	while (k < UNIFORM__COUNT)
	{
		uniforms->uniforms[k] = glGetUniformLocation(programid,
				g_uniforms_name[k]);
		if (uniforms->uniforms[k] < 0)
		{
			fprintf(stderr, "Couldn't find \"%s\" uniform\n",
				g_uniforms_name[k]);
			glDeleteProgram(programid);
			return (1);
		}
		++k;
	}
	return (0);
}

void	uniform_setmat4(
			t_uniforms *uniforms,
			t_uniform_id uid,
			const t_mat4 *mat
			)
{
	glUniformMatrix4fv(uniforms->uniforms[uid], 1, GL_FALSE, (GLfloat *)mat);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function                                                        * //
// *                                                                        * //
// ************************************************************************** //
