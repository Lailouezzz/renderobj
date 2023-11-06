/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objloader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:15:09 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/06 02:52:59 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file objloader.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The .obj loader utils definition.
 * @date 2023-11-06
 * @copyright Copyright (c) 2023
 */

#ifndef  OBJLOADER_H
# define OBJLOADER_H

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

# include <stdlib.h>
# include <stdio.h>

# include "utils/list.h"

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes                                                    * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Load object file into vram.
 * @param f The file stream containing the obj file.
 * @return t_list The list of VAO.
 */
t_list	obj_load(
			FILE *f
			);

#endif