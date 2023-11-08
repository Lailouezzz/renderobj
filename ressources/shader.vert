#version 400

layout (location=0) in vec3 position;
out float dist;

uniform mat4 mvp;

void	main()
{
	gl_Position =  mvp * vec4(position, 1.0);
	dist = gl_Position.z;
}
