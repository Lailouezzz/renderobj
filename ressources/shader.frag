#version 420

out vec4 fragColor;
in float dist;

struct colorgrad {
	vec3	color;
	float	level;
};

const vec3 deepocean = vec3(0.1, 0.1, 0.7);
const vec3 softocean = vec3(0.3, 0.3, 0.7);
const vec3 sand = vec3(1.00, 0.80, 0.00);
const vec3 verdureverte = vec3(0.03, 0.6, 0.00);
const vec3 verduremoinsverte = vec3(0.42, 0.63, 0.00);
const vec3 terre = vec3(0.63, 0.46, 0.00);
const vec3 roche = vec3(0.35, 0.25, 0.00);
const vec3 neige = vec3(1., 1., 1.);

const colorgrad colgrads[] = {
	colorgrad(deepocean, -6000.),
	colorgrad(softocean, 0.),
	colorgrad(sand, 0.),
	colorgrad(sand, 3.),
	colorgrad(verdureverte, 2.),
	colorgrad(verduremoinsverte, 600.),
	colorgrad(terre, 800.),
	colorgrad(roche, 2000.),
	colorgrad(roche, 2200.),
	colorgrad(neige, 2800.),
};

vec3	getcolor(float n)
{
	int	k;

	if (n < colgrads[0].level)
		return (colgrads[0].color);
	k = 1;
	while (k < colgrads.length())
	{
		if (n < colgrads[k].level)
			return mix(colgrads[k-1].color, colgrads[k].color, (n - colgrads[k-1].level) / (colgrads[k].level - colgrads[k-1].level));
		++k;
	}
	return (colgrads[colgrads.length() - 1].color);
}

void	main()
{
	fragColor = vec4(getcolor(dist), 1.);
}
