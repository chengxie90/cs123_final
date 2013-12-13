#version 330

in vec3 normalW;
in vec2 uv;
in float fogFactor;

uniform float near;
uniform float far;

uniform vec3 lightDir;
uniform vec3 lightColor;

uniform vec3 ambient;

uniform vec3 fogColor;

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
    
    color = mix(color, fogColor, fogFactor);

    fragColor = vec4(color, 1);
}
