#version 400

out vec4 fragColor;
in float dist;

void	main()
{
	float d = 2000.;
	fragColor = vec4((dist + 1000) / d, 1 - (dist + 1000) / d, 1 - (dist + 1000) / d, 1.);
}
