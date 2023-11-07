/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:13:05 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/07 17:49:41 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file renderer.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The renderer implementation.
 * @date 2023-11-07
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

#include <stdio.h>
#include <GL/glew.h>

#include "render/renderer.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper function prototypes                                             * //
// *                                                                        * //
// ************************************************************************** //

static int	_renderer_init_window(
				t_renderer_ctx *ctx,
				int width,
				int height,
				const char *title
				);

static void	_renderer_keycb(GLFWwindow *window,
				int key,
				int scancode,
				int action,
				int mods
				);


// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

int	renderer_init(t_renderer_ctx *ctx,
		int width,
		int height,
		const char *title
		)
{
	if (_renderer_init_window(ctx, width, height, title) != 0)
		return (1);
	glfwSetKeyCallback(ctx->window, _renderer_keycb);
	glfwMakeContextCurrent(ctx->window);
	glfwSwapInterval(1);
	return (0);
}

void	renderer_deinit(
			t_renderer_ctx *ctx
			)
{

	glfwDestroyWindow(ctx->window);
	glfwTerminate();
}

int	renderer_render(
		t_renderer_ctx *ctx
		)
{
	glViewport(0, 0, ctx->width, ctx->height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(ctx->window);
	glfwPollEvents();
	return (0);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function                                                        * //
// *                                                                        * //
// ************************************************************************** //

static int	_renderer_init_window(
				t_renderer_ctx *ctx,
				int width,
				int height,
				const char *title
				)
{
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	ctx->window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (ctx->window == NULL)
		return (1);
	glfwGetFramebufferSize(ctx->window, &ctx->width, &ctx->height);
	return (0);
}

static void	_renderer_keycb(GLFWwindow *window,
				int key,
				int scancode,
				int action,
				int mods
				)
{
	printf("code : %d\nscan : %d\naction : %d\nmods : %d\n",
		key, scancode, action, mods);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
