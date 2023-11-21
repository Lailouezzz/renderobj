/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfloader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 23:21:50 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/21 06:55:15 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file fdfloader.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The implementation of fdf loader.
 * @version 0.1
 * @date 2023-11-20
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils/list.h"
#include "math/vector.h"
#include "utils/fdfloader.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper function prototypes                                             * //
// *                                                                        * //
// ************************************************************************** //

t_fdf	fdf_load(
			FILE *f
			)
{
	char	buf[4096 * 16];
	int		t;
	int		x;
	int		y;
	char	*p;
	t_fdf	fdf;
	t_vec3f	vec;
	t_list	vertices;

	y = 0;
	x = 0;
	list_init(&vertices, sizeof(t_vec3f));
	while (fgets(buf, sizeof(buf), f) != NULL)
	{
		x = 0;
		p = buf;
		while (*p != '\0' && sscanf(p, "%d", &t) == 1)
		{
			vec = (t_vec3f){x, t, y};
			list_pushback(&vertices, &vec);
			while ((*p >= '0' && *p <= '9') || *p == '-')
				++p;
			while (*p == ' ')
				++p;
			++x;
		}
		++y;
	}
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.used * vertices.elemsize,
		vertices.data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	t_list	indices;
	GLuint	idx[3];

	list_init(&indices, sizeof(idx));
	fdf.width = x;
	fdf.height = y;
	y = 0;
	while (y < fdf.height - 1)
	{
		x = 0;
		while (x < fdf.width - 1)
		{
			idx[0] = y * fdf.width + x;
			idx[1] = y * fdf.width + x + 1;
			idx[2] = y * fdf.width + x + fdf.width;
			list_pushback(&indices, idx);
			idx[0] = y * fdf.width + x + 1;
			idx[1] = y * fdf.width + x + fdf.width + 1;
			idx[2] = y * fdf.width + x + fdf.width;
			list_pushback(&indices, idx);
			++x;
		}
		++y;
	}
	GLuint	ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.used * indices.elemsize,
		indices.data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	fdf.vao = vao;
	fdf.count = indices.used * indices.elemsize;
	return (fdf);
}
