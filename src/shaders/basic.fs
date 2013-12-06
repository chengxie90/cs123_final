#version 330

in vec3 normalW;
in vec3 positionW;

uniform vec3 lightDir;
uniform vec3 lightColor;

uniform vec3 eyePositionW;

uniform vec4 diffuse;
uniform vec4 ambient;
uniform vec4 specular;
uniform float shiness;

out vec4 fragColor;

void main()
{
    vec3 n = normalize(normalW);
    vec3 l = normalize(-lightDir);
    vec3 v = normalize(eyePositionW - positionW);
    
    vec3 h = normalize(v + l);

    vec3 brdf_phong = diffuse.xyz + specular.xyz * pow(max(0, dot(n, h)), 30);

    float cos_factor = max(0, dot(l, n));
    vec3 Li = l * cos_factor;

    vec3 color = Li * brdf_phong;

    fragColor = vec4(color, 1);
}
