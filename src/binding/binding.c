/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:39:21 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/21 07:07:55 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file binding.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The implementation of binding.
 * @date 2023-11-21
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

#include <string.h>
#include <GLFW/glfw3.h>

#include "binding/binding.h"

// ************************************************************************** //
// *                                                                        * //
// * Function header                                                        * //
// *                                                                        * //
// ************************************************************************** //

int	key_bind_init(
		t_bindings *bindings,
		void *ctx
		)
{
	size_t	k;

	bindings->ctx = ctx;
	memset(bindings->binding, 0, sizeof(bindings->binding));
	k = 0;
	while (k < KEY_BIND__COUNT)
	{
		bindings->binding[k].state = KEY_STATE_UP;
		bindings->binding[k].action = KEY_ACTION_NONE;
		++k;
	}
	return (0);
}

void	key_bind_destroy(
			t_bindings *bindings
			)
{
	(void)(bindings);
}

void	key_bind_process(
			t_bindings *bindings
			)
{
	size_t	k;

	k = 0;
	while (k < KEY_BIND__COUNT)
	{
		if (bindings->binding[k].action != KEY_ACTION_NONE)
		{
			if (bindings->binding[k].actionscb[bindings->binding[k].action]
				!= NULL)
				bindings->binding[k].actionscb[bindings->binding[k].action]
					(bindings->ctx, k, bindings->binding[k].cookie);
			bindings->binding[k].action = KEY_ACTION_NONE;
		}
		if (bindings->binding[k].statescb[bindings->binding[k].state] != NULL)
			bindings->binding[k].statescb[bindings->binding[k].state]
				(bindings->ctx, k, bindings->binding[k].cookie);
		++k;
	}
}

void	key_bind_poll(
			t_bindings *bindings,
			int keycode,
			int action
			)
{
	size_t	k;

	k = 0;
	while (k < KEY_BIND__COUNT)
	{
		if (bindings->binding[k].keycode == keycode)
		{
			if (action == GLFW_PRESS)
			{
				bindings->binding[k].action = KEY_ACTION_PRESS;
				bindings->binding[k].state = KEY_STATE_DOWN;
			}
			if (action == GLFW_RELEASE)
			{
				bindings->binding[k].action = KEY_ACTION_RELEASE;
				bindings->binding[k].state = KEY_STATE_UP;
			}
		}
		++k;
	}
}
void	key_bind_set_cookie(
			t_bindings *bindings,
			t_key_bind bind,
			void *cookie
			)
{
	bindings->binding[bind].cookie = cookie;
}

void	key_bind_set_statecb(
			t_bindings *bindings,
			t_key_bind bind,
			t_key_cb cb,
			t_key_state state
			)
{
	bindings->binding[bind].statescb[state] = cb;
}

void	key_bind_set_actioncb(
			t_bindings *bindings,
			t_key_bind bind,
			t_key_cb cb,
			t_key_action action
			)
{
	bindings->binding[bind].actionscb[action] = cb;
}

void	key_bind_set_keycode(
			t_bindings *bindings,
			t_key_bind bind,
			int keycode
			)
{
	bindings->binding[bind].keycode = keycode;
}
