struct Material
{
	vec4 color;
	
#ifdef DIFFUSE_MAP
	sampler2D diffuse;
#endif
	
#ifdef SPECULAR_REFLECTIONS

#ifdef SPECULAR_MAP
	sampler2D specular;
#else
	float specular;
#endif
    float shininess;
#endif
};
uniform Material material;

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
	
#ifdef SPECULAR_REFLECTIONS
    vec3 specular;
#endif
};  
uniform DirLight dirLight;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
#ifdef SPECULAR_REFLECTIONS
    vec3 specular;
#endif
};
#define NR_POINT_LIGHTS {MAX_NUMBER_OF_POINT_LIGHTS}
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int currentNumberOfPointLights;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 diffuseColor)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

#ifdef SPECULAR_REFLECTIONS
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 ambient  = light.ambient  * vec3(diffuseColor);
    vec3 diffuse  = light.diffuse  * diff * vec3(diffuseColor);
	
#ifdef SPECULAR_MAP
    vec3 specular = light.specular * spec * vec3(texture(material.specular, fs_in.texcoord));
#else
vec3 specular = light.specular * spec * vec3(material.specular);
#endif

    return (ambient + diffuse + specular);
#else
	vec3 ambient  = light.ambient  * vec3(diffuseColor);
    vec3 diffuse  = light.diffuse  * diff * vec3(diffuseColor);
    return (ambient + diffuse);
#endif
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 diffuseColor)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

#ifdef SPECULAR_REFLECTIONS
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
#endif

    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec3 ambient  = light.ambient  * vec3(diffuseColor);
    vec3 diffuse  = light.diffuse  * diff * vec3(diffuseColor);
	
#ifdef SPECULAR_REFLECTIONS

#ifdef SPECULAR_MAP
    vec3 specular = light.specular * spec * vec3(texture(material.specular, fs_in.texcoord));
#else
	vec3 specular = light.specular * spec * vec3(material.specular);
#endif
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
#else
	ambient  *= attenuation;
    diffuse  *= attenuation;
    return (ambient + diffuse);
#endif
}

vec4 GetDiffuse()
{
#ifdef DIFFUSE_MAP
	return texture(material.diffuse, fs_in.texcoord) * material.color;
#else
	return material.color;
#endif
}
