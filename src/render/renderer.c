/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:13:05 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/16 18:37:50 by ale-boud         ###   ########.fr       */
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

static t_mat4	*_renderer_get_mvp(
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
	if (_renderer_init_shader(ctx) != 0 || _renderer_init_buffer(ctx) != 0)
	{
		renderer_deinit(ctx);
		return (1);
	}
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
	t_mat4	mvp;

	usleep(16000);
	glViewport(0, 0, ctx->width, ctx->height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(ctx->uniforms.programid);
	uniform_setmat4(&ctx->uniforms, UNIFORM_MVP, _renderer_get_mvp(ctx, &mvp));
	glBindVertexArray(ctx->vao);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * 6);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	glUseProgram(0);
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
	static GLfloat	vecs[] = {
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};
	for (int k = 0; k < sizeof(vecs) / sizeof(*vecs); ++k)
	{
		vecs[k] /= 4.;
	}
	glGenVertexArrays(1, &ctx->vao);
	glBindVertexArray(ctx->vao);
	glGenBuffers(1, &ctx->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vecs), vecs, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return (0);
}

static void	_renderer_keycb(
				GLFWwindow *window,
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

static t_mat4	*_renderer_get_mvp(
					t_renderer_ctx *ctx,
					t_mat4 *rmat
					)
{
	static float	x = 0.;
	t_mat4			tmp;

	x += 0.01;
	mat_lookatmat4(&tmp, &(t_vec3f){cos(x) * 2., 1., sin(x) * 2.},
		&(t_vec3f){sin(x * 4), 0., cos(x * 2)}, &(t_vec3f){0., 1., 0.});
	mat_projperspmat4(rmat, 1.4, ctx->width, ctx->height);
	return (mat_mat4xmat4(rmat, rmat, &tmp));
}
