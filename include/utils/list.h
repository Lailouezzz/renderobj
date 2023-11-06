/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:22:56 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/06 02:36:18 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file list.h
 * @author your name (you@domain.com)
 * @brief The definition of a dynamic list.
 * @date 2023-11-06
 * @copyright Copyright (c) 2023
 */

#ifndef  LIST_H
# define LIST_H


// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include <stddef.h>

// ************************************************************************** //
// *                                                                        * //
// * Structure definition                                                   * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @struct s_list
 * @brief Definition of a dynamic list.
 */
typedef struct s_list {
	void	*data;
	size_t	used;
	size_t	alloced;
	size_t	elemsize;
}	t_list;

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes                                                    * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Initialize the list.
 * @param l The #s_list.
 * @param elemsize Size of 1 elem.
 * @return int 0 if success. non-null value if malloc error.
 */
int		list_init(
			t_list *l,
			size_t elemsize
			);

/**
 * @brief The len of the #s_list
 * @param l The #s_list
 * @return size_t The len of the #s_list.
 */
size_t	list_len(
			const t_list *l
			);

/**
 * @brief Pushback elem to the #s_list.
 * @param l The #s_list.
 * @param elem The elem
 * @return int 0 if success. non-null value if malloc error.
 */
int		list_pushback(
			t_list *l,
			void *elem
			);

#endif
