/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:28:37 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/03 17:33:57 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file dvb.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Dynamic size vertex buffer.
 * @date 2023-11-03
 * @copyright Copyright (c) 2023
 */

#ifndef  DVB_H
# define DVB_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include <GL/glew.h>

# include "math/vector.h"
# include "buffer/vb.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definition                                                   * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @struct s_dvb
 * @brief Definition of a dynamic size vertex buffer.
 */
typedef struct s_dvb {
	/**
	 * @brief The vertices.
	 */
	t_vec3f	*vertices;

	/**
	 * @brief The number of vertices in #vertices.
	 */
	size_t	size;

	/**
	 * @brief Number of vertices alloced in #vertices.
	 */
	size_t	alloced;
}	t_dvb;

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes                                                    * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Create a #s_dvb.
 * @return #s_dvb* created #s_dvb.
 */
t_dvb	*dvb_init(void);

/**
 * @brief Create a #s_dvb from a #s_vb.
 * @param vb The #s_vb to copy.
 * @return #s_dvb* created dvb.
 */
t_dvb	*dvb_init_vb(
			const t_vb *vb
			);

/**
 * @brief Destroy a #s_dvb.
 * @param dvb The #s_dvb to destroy.
 */
void	dvb_destroy(
			t_dvb *dvb
			);

/**
 * @brief Erase a #s_dvb.
 * @param dvb The #s_dvb to erase.
 */
void	dvb_erase(
			t_dvb *dvb
			);

/**
 * @brief Insert a #s_vec3f into the back of a #s_dvb.
 * @param dvb The #s_dvb.
 * @param vec The #s_vec3f to insert back.
 * @return int @c 0 if success. non-null value if error.
 */
int		dvb_insert_back(
			t_dvb *dvb,
			const t_vec3f *vec
			);

/**
 * @brief Pop back a #s_vec3f of a #s_dvb.
 * @param dvb The #s_dvb.
 * @param vec The #s_vec3f popped.
 * @return int @c 0 if success. non-null value if error.
 */
int		dvb_pop_back(
			t_dvb *dvb,
			t_vec3f *vec
			);

#endif
