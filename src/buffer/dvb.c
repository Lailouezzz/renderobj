/**
 * @file dvb.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The dynamic size vertex buffer implementation.
 * @date 2023-11-03
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Include                                                                * //
// *                                                                        * //
// ************************************************************************** //

#include <stdlib.h>
#include <string.h>

#include "buffer/dvb.h"

// ************************************************************************** //
// *                                                                        * //
// * Function implementation                                                * //
// *                                                                        * //
// ************************************************************************** //

t_dvb	*dvb_init(void)
{
	t_dvb	*dvb;

	dvb = malloc(sizeof(*dvb));
	if (dvb == NULL)
		return (NULL);
	dvb->alloced = 1;
	dvb->vertices = malloc(sizeof(*dvb->vertices) * dvb->alloced);
	if (dvb->vertices == NULL)
	{
		free(dvb);
		return (NULL);
	}
	dvb->size = 0;
	return (dvb);
}

t_dvb	*dvb_init_vb(
			const t_vb *vb
			)
{
	(void)(vb);
	// TODO: flemme
	return (NULL);
}

void	dvb_destroy(
			t_dvb *dvb
			)
{
	if (dvb != NULL)
	{
		if (dvb->vertices != NULL)
			free(dvb->vertices);
		free(dvb);
	}
}

void	dvb_erase(
			t_dvb *dvb
			)
{
	dvb->size = 0;
}

int	dvb_insert_back(
		t_dvb *dvb,
		const t_vec3f *vec
		)
{
	(void)(dvb);
	(void)(vec);
	return (0);
}

int	dvb_pop_back(
		t_dvb *dvb,
		t_vec3f *vec
		)
{
	(void)(dvb);
	(void)(vec);
	return (0);
}
