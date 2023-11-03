/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vb.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:20:05 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/03 17:00:51 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file vb.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Fixed size vertex buffer definition.
 * @date 2023-11-03
 * @copyright Copyright (c) 2023
 */

#ifndef  VB_H
# define VB_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include <GL/glew.h>

# include "math/vector.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definition                                                   * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @struct s_vb
 * @brief Definition of a fixed size vertex buffer.
 */
typedef struct s_vb {
	/**
	 * @brief The vertices.
	 */
	t_vec3f	*vertices;

	/**
	 * @brief The number of vertices in #vertices.
	 */
	size_t	size;
}	t_vb;

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes                                                    * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Create a #s_vb.
 * @param size Number of vertices.
 * @return #s_vb* created #s_vb.
 */
t_vb	*vb_init(
			size_t size
			);

/**
 * @brief Destroy a #s_vb.
 * @param vb #s_vb to destroy.
 */
void	vb_destroy(
			t_vb *vb
			);

#endif
