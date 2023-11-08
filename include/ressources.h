/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:58:37 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/08 12:48:31 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ressources.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Ressources extern symbols.
 * @date 2023-11-04
 * @copyright Copyright (c) 2023
 */

#ifndef  RESSOURCES_H
# define RESSOURCES_H

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

# include <stdint.h>
# include <stddef.h>

// ************************************************************************** //
// *                                                                        * //
// * Extern symbols                                                         * //
// *                                                                        * //
// ************************************************************************** //

extern char	res_shader_vert[]
	asm("_binary_ressources_shader_vert_start");

extern char	res_shader_vert_end[]
	asm("_binary_ressources_shader_vert_end");

extern char	res_shader_frag[]
	asm("_binary_ressources_shader_frag_start");

extern char	res_shader_frag_end[]
	asm("_binary_ressources_shader_frag_end");

#endif
