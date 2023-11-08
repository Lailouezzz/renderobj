/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:06:17 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/08 19:15:53 by ale-boud         ###   ########.fr       */
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

	if (renderer_init(&ctx, 800, 800, "test") != 0)
		return (EXIT_FAILURE);
	while (glfwWindowShouldClose(ctx.window) == 0)
	{
		renderer_render(&ctx);
	}
	renderer_deinit(&ctx);
	return (EXIT_SUCCESS);
}
