#version 400

out vec4 fragColor;
in float dist;

void	main()
{
	fragColor = vec4(0., 1. - dist / 2., 1. - dist / 2., 1.);
}
