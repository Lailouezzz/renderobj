/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:06:17 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/07 17:45:06 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "render/renderer.h"

int	main(void)
{
	t_renderer_ctx	ctx;

	if (!glfwInit())
		return (EXIT_FAILURE);
	glewExperimental = GL_TRUE;
	glewInit();
	if (renderer_init(&ctx, 500, 500, "test") != 0)
		return (EXIT_FAILURE);
	while (glfwWindowShouldClose(ctx.window) == 0)
	{
		renderer_render(&ctx);
	}
	renderer_deinit(&ctx);
	return (EXIT_SUCCESS);
}
