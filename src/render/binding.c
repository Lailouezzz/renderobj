/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 06:04:26 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/21 13:46:07 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file binding.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The binding functionnality for the renderer.
 * @date 2023-11-21
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

#include <math.h>

#include "render/renderer.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper struct                                                          * //
// *                                                                        * //
// ************************************************************************** //

typedef struct s_binding_def {
	t_key_bind		bind;
	t_key_action	action;
	t_key_state		state;
	int				keycode;
	t_key_cb		cb;
}	t_binding_def;

typedef struct s_cookie {
	float	xrot;
	float	yrot;
	int		curproj;
}	t_cookie;

// ************************************************************************** //
// *                                                                        * //
// * Callback function prototypes                                           * //
// *                                                                        * //
// ************************************************************************** //

static void	_exitcb(
				t_renderer_ctx *ctx,
				t_key_bind bind,
				t_cookie *cookie
				);

static void	_transcb(
				t_renderer_ctx *ctx,
				t_key_bind bind,
				t_cookie *cookie
				);

static void	_rotcb(
				t_renderer_ctx *ctx,
				t_key_bind bind,
				t_cookie *cookie
				);

static void	_zoomcb(
				t_renderer_ctx *ctx,
				t_key_bind bind,
				t_cookie *cookie
				);

static void	_zmulcb(
				t_renderer_ctx *ctx,
				t_key_bind bind,
				t_cookie *cookie
				);

const t_binding_def	g_bindingsdef[] = {
{KEY_BIND_EXIT,
	KEY_ACTION_PRESS, 0, GLFW_KEY_ESCAPE, (t_key_cb)_exitcb},
{KEY_BIND_FORWARD,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_W, (t_key_cb)_transcb},
{KEY_BIND_BACKWARD,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_S, (t_key_cb)_transcb},
{KEY_BIND_LEFT,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_A, (t_key_cb)_transcb},
{KEY_BIND_RIGHT,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_D, (t_key_cb)_transcb},
{KEY_BIND_ROTUP,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_I, (t_key_cb)_rotcb},
{KEY_BIND_ROTDOWN,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_K, (t_key_cb)_rotcb},
{KEY_BIND_ROTLEFT,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_J, (t_key_cb)_rotcb},
{KEY_BIND_ROTRIGHT,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_L, (t_key_cb)_rotcb},
{KEY_BIND_UP,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_R, (t_key_cb)_transcb},
{KEY_BIND_DOWN,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_F, (t_key_cb)_transcb},
{KEY_BIND_ZOOMIN,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_T, (t_key_cb)_zoomcb},
{KEY_BIND_ZOOMOUT,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_G, (t_key_cb)_zoomcb},
{KEY_BIND_ZMULP,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_X, (t_key_cb)_zmulcb},
{KEY_BIND_ZMULM,
	KEY_ACTION_NONE, KEY_STATE_DOWN, GLFW_KEY_Z, (t_key_cb)_zmulcb},
};

// ************************************************************************** //
// *                                                                        * //
// * Header private function                                                * //
// *                                                                        * //
// ************************************************************************** //

int	_renderer_init_binding(
		t_renderer_ctx *ctx
		)
{
	size_t		k;
	t_cookie	*cookie;

	cookie = malloc(sizeof(cookie));
	if (cookie == NULL)
		return (1);
	cookie->xrot = 0;
	cookie->yrot = 0;
	cookie->curproj = 0;
	if (key_bind_init(&ctx->bindings, ctx) != 0)
		return (1);
	k = 0;
	while (k < sizeof(g_bindingsdef) / sizeof(*g_bindingsdef))
	{
		if (g_bindingsdef[k].action != KEY_ACTION_NONE)
			key_bind_set_actioncb(&ctx->bindings, g_bindingsdef[k].bind,
				g_bindingsdef[k].cb, g_bindingsdef[k].action);
		else
			key_bind_set_statecb(&ctx->bindings, g_bindingsdef[k].bind,
				g_bindingsdef[k].cb, g_bindingsdef[k].state);
		key_bind_set_keycode(&ctx->bindings, g_bindingsdef[k].bind,
			g_bindingsdef[k].keycode);
		key_bind_set_cookie(&ctx->bindings, g_bindingsdef[k].bind, cookie);
		++k;
	}
	return (0);
}

void	_renderer_deinit_binding(
			t_renderer_ctx *ctx
			)
{
	free(ctx->bindings.binding[g_bindingsdef[0].bind].cookie);
	key_bind_destroy(&ctx->bindings);
}

// ************************************************************************** //
// *                                                                        * //
// * Callback function                                                      * //
// *                                                                        * //
// ************************************************************************** //

static void	_exitcb(
				t_renderer_ctx *ctx,
				t_key_bind bind,
				t_cookie *cookie
				)
{
	(void)(bind);
	(void)(cookie);
	glfwSetWindowShouldClose(ctx->window, 1);
}

static void	_transcb(
				t_renderer_ctx *ctx,
				t_key_bind bind,
				t_cookie *cookie
				)
{
	t_vec3f	tmp;

	(void)(cookie);
	if (bind == KEY_BIND_FORWARD)
		vec_vec3add(&ctx->cam, &ctx->cam, &ctx->focal);
	if (bind == KEY_BIND_BACKWARD)
		vec_vec3sub(&ctx->cam, &ctx->cam, &ctx->focal);
	if (bind == KEY_BIND_LEFT)
		vec_vec3sub(&ctx->cam, &ctx->cam, vec_vec3normalize(&tmp,
				vec_vec3cross(&tmp, &ctx->focal, &(t_vec3f){0., 1., 0.})));
	if (bind == KEY_BIND_RIGHT)
		vec_vec3sub(&ctx->cam, &ctx->cam, vec_vec3normalize(&tmp,
				vec_vec3cross(&tmp, &(t_vec3f){0., 1., 0.}, &ctx->focal)));
	if (bind == KEY_BIND_UP)
		ctx->cam.y += 0.75;
	if (bind == KEY_BIND_DOWN)
		ctx->cam.y -= 0.75;
}

static void	_rotcb(
				t_renderer_ctx *ctx,
				t_key_bind bind,
				t_cookie *cookie
				)
{
	if (bind == KEY_BIND_ROTDOWN)
		cookie->yrot += 0.05;
	if (bind == KEY_BIND_ROTUP)
		cookie->yrot -= 0.05;
	if (bind == KEY_BIND_ROTLEFT)
		cookie->xrot -= 0.05;
	if (bind == KEY_BIND_ROTRIGHT)
		cookie->xrot += 0.05;
	ctx->focal.x = -((cos(cookie->xrot)) * (cos(cookie->yrot)));
	ctx->focal.z = -((-sin(cookie->xrot)) * (-cos(cookie->yrot)));
	ctx->focal.y = (-sin(cookie->yrot));
}

static void	_zoomcb(
				t_renderer_ctx *ctx,
				t_key_bind bind,
				t_cookie *cookie
				)
{
	(void)(cookie);

	if (bind == KEY_BIND_ZOOMIN)
		ctx->fov -= 0.005;
	if (bind == KEY_BIND_ZOOMOUT)
		ctx->fov += 0.005;
}

static void	_zmulcb(
				t_renderer_ctx *ctx,
				t_key_bind bind,
				t_cookie *cookie
				)
{
	(void)(cookie);

	if (bind == KEY_BIND_ZMULP)
		ctx->zmul += 0.0005;
	if (bind == KEY_BIND_ZMULM)
		ctx->zmul -= 0.0005;
}
