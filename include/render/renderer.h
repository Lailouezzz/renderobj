/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:32:52 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/21 09:46:29 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file renderer.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The renderer definition.
 * @date 2023-11-07
 * @copyright Copyright (c) 2023
 */

#ifndef  RENDERER_H
# define RENDERER_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include <GL/glew.h>
# include <GLFW/glfw3.h>

# include "utils/fdfloader.h"
# include "binding/binding.h"
# include "render/uniform.h"
# include "math/matrix.h"

// ************************************************************************** //
// *                                                                        * //
// * Struct definition                                                      * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @todo Doc
 */
typedef struct s_renderer_ctx {
	/* MESH */
	t_fdf		fdf;
	t_vec3f		cam;
	t_vec3f		focal;
	int			width;
	int			height;
	float		fov;
	GLfloat		zmul;
	t_uniforms	uniforms;
	t_bindings	bindings;
	GLFWwindow	*window;
}	t_renderer_ctx;

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes                                                    * //
// *                                                                        * //
// ************************************************************************** //

int		renderer_init(
			t_renderer_ctx *ctx,
			int width,
			int height,
			const char *title
			);

void	renderer_deinit(
			t_renderer_ctx *ctx
			);

int		renderer_render(
			t_renderer_ctx *ctx
			);

// ************************************************************************** //
// *                                                                        * //
// * Private function                                                       * //
// *                                                                        * //
// ************************************************************************** //


int		_renderer_init_binding(
			t_renderer_ctx *ctx
			);

#endif