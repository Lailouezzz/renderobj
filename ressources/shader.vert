#version 400

layout (location=0) in vec3 position;
out float dist;

uniform mat4 view;
uniform mat4 proj;
uniform float zmul;

#define M_PI 3.1415926535897932384626433832795

void	main()
{
	dist = position.y;
	vec3	trans = vec3((position.x - 2559. / 2.) / 2559., position.y * zmul, (position.z - 1130. / 2.) / 1130.);
	vec3	rvec;
	rvec.z = cos(trans.x * M_PI * 2) * cos(trans.z * M_PI) * 1000. + cos(trans.x * M_PI * 2) * cos(trans.z * M_PI) * trans.y;
	rvec.x = sin(trans.x * M_PI * 2) * cos(trans.z * M_PI) * 1000. + sin(trans.x * M_PI * 2) * cos(trans.z * M_PI) * trans.y;
	rvec.y = -sin(trans.z * M_PI) * 1000. + (-sin(trans.z * M_PI)) * trans.y;
	gl_Position =  proj * view * vec4(rvec.x / 10., rvec.y / 10., rvec.z / 10., 1.0);
}
