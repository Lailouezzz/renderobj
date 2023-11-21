#version 400

layout (location=0) in vec3 position;
out float dist;

uniform mat4 view;
uniform mat4 proj;
uniform float zmul;

void	main()
{
	dist = position.y;
	gl_Position =  proj * view * vec4(position.x, position.y * zmul, position.z, 1.0);
}
