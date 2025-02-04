#version 460

in vec2 texcoord_fs;

#exposed
uniform sampler2D screen_texture;
uniform vec2 screen_size = vec2(600.0, 600.0);
uniform int bloom_size = 50;
uniform float bloom_threshold = 1.5;
#end_exposed

out vec4 fs_color;

float gaussian(int x, int y, float sigma)
{
	float E = 2.71828;
	float PI = 3.141592653;
	float twoSigmaSqr = 2 * sigma * sigma;
	return (1 / sqrt(PI * twoSigmaSqr)) * pow(E, -(x * x + y * y) / (2 * twoSigmaSqr));
}

vec4 blur()
{
	vec3 color = vec3(0.0, 0.0, 0.0);
	float kernelSum = 0.0;
	float sigma = bloom_size / 8.0f;

	int upper = ((bloom_size - 1) / 2);
	int lower = -upper;

	for (int x = lower; x <= upper; ++x)
	{
		for (int y = lower; y <= upper; ++y)
		{
			vec2 uv = texcoord_fs + vec2(x * (1 / screen_size.x), y * (1 / screen_size.y));
			vec3 screen_color = texture(screen_texture, uv).xyz;
			if (length(screen_color) < bloom_threshold)
				screen_color = vec3(0.0, 0.0, 0.0);
			float gauss = gaussian(x, y, sigma);
			kernelSum += gauss;
			color += max(vec3(0.0, 0.0, 0.0), gauss * screen_color);
		}
	}

	color /= kernelSum;

	return vec4(color, 1.0f);
}

float luminance(vec3 v)
{
    return dot(v, vec3(0.2126f, 0.7152f, 0.0722f));
}

vec3 reinhard_jodie(vec3 v)
{
    float l = luminance(v);
    vec3 tv = v / (1.0f + v);
    return mix(v / (1.0f + l), tv, tv);
}

void main()
{
	vec4 bloom =  max(vec4(0.0, 0.0, 0.0, 1.0), blur());
	vec4 hdr = texture(screen_texture, texcoord_fs) + bloom;
	vec3 mapped = reinhard_jodie(hdr.xyz);
	fs_color = vec4(mapped, 1.0);
}