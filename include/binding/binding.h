/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binding.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:43:43 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/21 09:44:12 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file binding.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The binding definition.
 * @date 2023-11-07
 * @copyright Copyright (c) 2023
 */

#ifndef  BINDING_H
# define BINDING_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

// ************************************************************************** //
// *                                                                        * //
// * Struct definition                                                      * //
// *                                                                        * //
// ************************************************************************** //

typedef enum e_key_state {
	KEY_STATE_DOWN,
	KEY_STATE_UP,
	KEY_STATE__COUNT,
}	t_key_state;

typedef enum e_key_action {
	KEY_ACTION_PRESS,
	KEY_ACTION_RELEASE,
	KEY_ACTION__COUNT,
	KEY_ACTION_NONE,
}	t_key_action;

typedef enum e_key_bind {
	KEY_BIND_EXIT,
	KEY_BIND_FORWARD,
	KEY_BIND_BACKWARD,
	KEY_BIND_LEFT,
	KEY_BIND_RIGHT,
	KEY_BIND_ROTUP,
	KEY_BIND_ROTDOWN,
	KEY_BIND_ROTLEFT,
	KEY_BIND_ROTRIGHT,
	KEY_BIND_UP,
	KEY_BIND_DOWN,
	KEY_BIND_PROJ,
	KEY_BIND_ZOOMIN,
	KEY_BIND_ZOOMOUT,
	KEY_BIND_ZMULP,
	KEY_BIND_ZMULM,
	KEY_BIND__COUNT,
}	t_key_bind;

typedef void	(*t_key_cb)(void *, t_key_bind, void *);

typedef struct s_binding {
	t_key_cb		statescb[KEY_STATE__COUNT];
	t_key_cb		actionscb[KEY_ACTION__COUNT];
	t_key_action	action;
	t_key_state		state;
	int				keycode;
	void			*cookie;
}	t_binding;

typedef struct s_bindings {
	t_binding	binding[KEY_BIND__COUNT];
	void		*ctx;
}	t_bindings;

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes                                                    * //
// *                                                                        * //
// ************************************************************************** //

int		key_bind_init(
			t_bindings *bindings,
			void *ctx
			);

void	key_bind_destroy(
			t_bindings *bindings
			);

void	key_bind_process(
			t_bindings *bindings
			);

void	key_bind_poll(
			t_bindings *bindings,
			int keycode,
			int action
			);

void	key_bind_set_cookie(
			t_bindings *bindings,
			t_key_bind bind,
			void *cookie
			);

void	key_bind_set_statecb(
			t_bindings *bindings,
			t_key_bind bind,
			t_key_cb cb,
			t_key_state state
			);

void	key_bind_set_actioncb(
			t_bindings *bindings,
			t_key_bind bind,
			t_key_cb cb,
			t_key_action action
			);

void	key_bind_set_keycode(
			t_bindings *bindings,
			t_key_bind bind,
			int keycode
			);

#endif
