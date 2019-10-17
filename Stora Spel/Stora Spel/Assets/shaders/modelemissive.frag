#version 440 core

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_emission;

in vec3 frag_pos;
in vec2 v_tex;
in vec3 v_normal;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform sampler2D texture_emissive;

// from file "shading.frag"
vec3 shading(vec3 position, vec3 normal);
vec3 dither();

void main()
{
	vec3 normal = normalize(v_normal);
	vec4 surface_color = texture(texture_diffuse, v_tex);
	float alpha = surface_color.a;
	//surface_color = vec3(1,0,0);

	float emission_strength = texture(texture_emissive, v_tex).r;
	vec3 shading = shading(frag_pos, normal);
	vec3 color = surface_color.rgb * mix(shading, vec3(1), emission_strength);

	//color = vec3(texture(texture_emissive, v_tex).rgb);

	color += dither();
	out_color = vec4(color, alpha);

	// TODO: maybe use alpha channel instead
	out_emission = vec4(emission_strength * surface_color.rgb, 1);
}