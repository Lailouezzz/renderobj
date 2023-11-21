/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:13:05 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/21 14:42:52 by ale-boud         ###   ########.fr       */
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
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <GL/glew.h>

#include "render/shader.h"
#include "render/renderer.h"
#include "utils/fdfloader.h"

#include "ressources.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper function prototypes                                             * //
// *                                                                        * //
// ************************************************************************** //

static int		_renderer_init_window(
					t_renderer_ctx *ctx,
					int width,
					int height,
					const char *title
					);

static int		_renderer_init_shader(
					t_renderer_ctx *ctx
					);

static int		_renderer_init_buffer(
					t_renderer_ctx *ctx
					);

static void		_renderer_keycb(
					GLFWwindow *window,
					int key,
					int scancode,
					int action,
					int mods
					);

static void		_renderer_close_keycb(
					GLFWwindow *window
					);

static void		_renderer_sizecb(
					GLFWwindow *window,
					int width,
					int height
					);

static t_mat4	*_renderer_get_view(
					t_renderer_ctx *ctx,
					t_mat4 *rmat
					);

// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

int	renderer_init(
		t_renderer_ctx *ctx,
		int width,
		int height,
		const char *title
		)
{
	GLenum	gst;

	memset(ctx, 0, sizeof(*ctx));
	if (_renderer_init_window(ctx, width, height, title) != 0)
	{
		renderer_deinit(ctx);
		return (1);
	}
	gst = glewInit();
	if (gst != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(gst));
		renderer_deinit(ctx);
		return (1);
	}
	ctx->uniforms.programid = 0;
	if (_renderer_init_shader(ctx) != 0
		|| _renderer_init_buffer(ctx) != 0 || _renderer_init_binding(ctx) != 0)
	{
		renderer_deinit(ctx);
		return (1);
	}
	ctx->fov = 1.5;
	glEnable(GL_DEPTH_TEST);
	return (0);
}

void	renderer_deinit(
			t_renderer_ctx *ctx
			)
{
	glDeleteProgram(ctx->uniforms.programid);
	if (ctx->window != NULL)
		glfwDestroyWindow(ctx->window);
	glfwTerminate();
}

int	renderer_render(
		t_renderer_ctx *ctx
		)
{
	t_mat4	tmp;

	usleep(1000);
	glViewport(0, 0, ctx->width, ctx->height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(ctx->uniforms.programid);
	uniform_setmat4(&ctx->uniforms, UNIFORM_VIEW,
		_renderer_get_view(ctx, &tmp));
	uniform_setmat4(&ctx->uniforms, UNIFORM_PROJ,
		mat_mat4ident(&tmp));
	uniform_setfloat(&ctx->uniforms, UNIFORM_ZMUL, ctx->zmul);

	glBindVertexArray(ctx->fdf.vao);
	glDrawElements(GL_TRIANGLES, ctx->fdf.count, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
	glUseProgram(0);
	glfwSwapBuffers(ctx->window);
	glfwPollEvents();
	key_bind_process(&ctx->bindings);
	return (0);
}

// ************************************************************************** //
// *                                                                        * //
// * Init function                                                          * //
// *                                                                        * //
// ************************************************************************** //

static int	_renderer_init_window(
				t_renderer_ctx *ctx,
				int width,
				int height,
				const char *title
				)
{
	if (glfwInit() != GL_TRUE)
		return (1);
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glewExperimental = GL_TRUE;
	ctx->window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (ctx->window == NULL)
		return (1);
	glfwGetFramebufferSize(ctx->window, &ctx->width, &ctx->height);
	glfwSetWindowUserPointer(ctx->window, ctx);
	glfwSetKeyCallback(ctx->window, _renderer_keycb);
	glfwSetWindowSizeCallback(ctx->window, _renderer_sizecb);
	glfwSetWindowCloseCallback(ctx->window, _renderer_close_keycb);
	glfwMakeContextCurrent(ctx->window);
	glfwSwapInterval(1);
	return (0);
}

static int	_renderer_init_shader(
				t_renderer_ctx *ctx
				)
{
	GLint	sv;
	GLint	sf;
	GLint	programid;

	sv = shader_compile(res_shader_vert, res_shader_vert_end - res_shader_vert,
			GL_VERTEX_SHADER);
	if (sv == 0)
		return (1);
	sf = shader_compile(res_shader_frag, res_shader_frag_end - res_shader_frag,
			GL_FRAGMENT_SHADER);
	if (sf == 0)
	{
		glDeleteShader(sv);
		return (1);
	}
	programid = shader_link(sv, sf);
	if (programid == 0)
	{
		glDeleteShader(sv);
		glDeleteShader(sf);
		return (1);
	}
	return (uniform_init(&ctx->uniforms, programid));
}

static int	_renderer_init_buffer(
				t_renderer_ctx *ctx
				)
{
	ctx->fdf = fdf_load(fopen("42.fdf", "r"));
	ctx->zmul = 0.005;
	return (0);
}

// ************************************************************************** //
// *                                                                        * //
// * Callback function                                                      * //
// *                                                                        * //
// ************************************************************************** //

static void	_renderer_keycb(
				GLFWwindow *window,
				int key,
				int scancode,
				int action,
				int mods
				)
{
	t_renderer_ctx	*ctx;

	(void)(scancode);
	(void)(mods);
	ctx = glfwGetWindowUserPointer(window);
	key_bind_poll(&ctx->bindings, key, action);
}

static void	_renderer_sizecb(
				GLFWwindow *window,
				int width,
				int height
				)
{
	t_renderer_ctx	*ctx;

	ctx = glfwGetWindowUserPointer(window);
	ctx->width = width;
	ctx->height = height;
}

static void	_renderer_close_keycb(
				GLFWwindow *window
				)
{
	glfwWindowShouldClose(window);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function                                                        * //
// *                                                                        * //
// ************************************************************************** //

static t_mat4	*_renderer_get_view(
					t_renderer_ctx *ctx,
					t_mat4 *rmat
					)
{
	static float	x = 0.;
	t_mat4			tmp;
	t_vec3f			at;

	x += 0.01;
	mat_lookatmat4(&tmp, &ctx->cam,
		vec_vec3add(&at, &ctx->cam, &ctx->focal), &(t_vec3f){0., 1., 0.});
	mat_projperspmat4(rmat, ctx->fov, ctx->width, ctx->height);
	return (mat_mat4xmat4(rmat, rmat, &tmp));
}
