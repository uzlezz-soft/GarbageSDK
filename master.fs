#version 330 core

// fragment shader

{DEFINES}

@INCLUDE(simple_lighting.si)

out vec4 FragColor;

in VertexOutput
{
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 texcoord;
} fs_in;

uniform float time;
uniform vec3 viewPos;
uniform Material material;

void main()
{
	vec4 diffuse = GetDiffuse();

#ifdef ALPHA_CLIP
	if (diffuse.a < 0.5)
	{
		discard;
	}
#endif

    // properties
    vec3 norm = normalize(fs_in.normal);
    vec3 viewDir = normalize(viewPos - fs_in.position);

    // Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir, diffuse);

    // Point lights
    for(int i = 0; i < currentNumberOfPointLights; i++)
    {
        result += CalcPointLight(pointLights[i], norm, fs_in.position, viewDir, diffuse);
    }
    
    FragColor = vec4(result, 1.0);
}