/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:06:17 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/04 15:16:18 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils/shader.h"
#include "ressources.h"

int	main(void)
{
	if (!glfwInit())
		return (EXIT_FAILURE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return (EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	printf("Renderer: %s\nVersion: %s\n", glGetString(GL_RENDERER),
		glGetString(GL_VERSION));
	printf("ret: %d\n", shader_compile(res_shader_vert, res_shader_vert_end - res_shader_vert, GL_VERTEX_SHADER));
	glfwDestroyWindow(window);
	glfwTerminate();
	return (EXIT_SUCCESS);
}
