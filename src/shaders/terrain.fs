#version 330

in vec3 normalW;
in vec3 positionW;
in vec2 uv;

uniform vec3 lightDir;
uniform vec3 lightColor;

uniform vec3 ambient;

uniform sampler2D diffuseMap;

out vec4 fragColor;

void main()
{
    vec3 n = normalize(normalW);
    vec3 l = normalize(-lightDir);

    vec3 brdf_diffuse = texture(diffuseMap, uv * 15).xyz;

    float cos_factor = max(0, dot(l, n));
    vec3 Li = lightColor * cos_factor;

    vec3 color = Li * brdf_diffuse;
    color += ambient * brdf_diffuse;

    fragColor = vec4(color, 1);
}
