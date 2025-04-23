#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform vec3 viewPos;

struct DirLight {
    vec4 Color;
    vec3 Direction;
};

struct PointLight {
    vec4 Color;
    vec3 Position;
    float ConstantAttenuation;
    float LinearAttenuation;
    float QuadraticAttenuation;
};

struct SpotLight {

    vec4 Color;
    vec3 Position;
    vec3 Direction;
    float InnerCutoff;
    float OuterCutoff;
    float ConstantAttenuation;
    float LinearAttenuation;
    float QuadraticAttenuation;
};

#define NR_DIR_LIGHTS 12
#define NR_POINT_LIGHTS 12
#define NR_SPOT_LIGHTS 12

uniform DirLight dirLights[NR_DIR_LIGHTS];
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

uniform int DirLightNb;
uniform int PointLightNb;
uniform int SpotLightNb;

vec3 DirLightComputation(DirLight dirLight, vec3 FragPos, vec3 Normal, vec3 Diffuse, float Specular, vec3 ViewDir)
{
    vec3 diffuse = max(dot(Normal, dirLight.Direction), 0.0) * Diffuse * dirLight.Color.rgb * dirLight.Color.a;
    return diffuse;
}

vec3 PointLightComputation(PointLight pointLight, vec3 FragPos, vec3 Normal, vec3 Diffuse, float Specular, vec3 ViewDir)
{
    // diffuse
    vec3 lightDir = normalize(pointLight.Position - FragPos);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * pointLight.Color.rgb * pointLight.Color.a;
    // specular
    vec3 halfwayDir = normalize(lightDir + ViewDir);
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
    vec3 specular = pointLight.Color.rgb * pointLight.Color.a * spec * Specular;
    // attenuation
    float distance = length(pointLight.Position - FragPos);
    float attenuation = 1.0 / (pointLight.ConstantAttenuation + pointLight.LinearAttenuation * distance + pointLight.QuadraticAttenuation * distance * distance);
    diffuse *= attenuation;
    specular *= attenuation;
    return diffuse + specular;
}

vec3 SpotLightComputation(SpotLight spotLight, vec3 FragPos, vec3 Normal, vec3 Diffuse, float Specular, vec3 ViewDir)
{
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(spotLight.Position - FragPos);

    if (dot(-lightDir, spotLight.Direction) > spotLight.OuterCutoff)
    {
        vec3 diffuse = max(dot(norm, lightDir), 0.0) * Diffuse * spotLight.Color.rgb * spotLight.Color.a;
        // specular
        vec3 halfwayDir = normalize(lightDir + ViewDir);
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
        vec3 specular = spotLight.Color.rgb * spotLight.Color.a * spec * Specular;
        // intensity
        float theta = dot(lightDir, normalize(-spotLight.Direction));
        float epsilon = (spotLight.InnerCutoff - spotLight.OuterCutoff);
        float intensity = clamp((theta - spotLight.OuterCutoff) / epsilon, 0.0, 1.0);
        diffuse *= intensity;
        specular *= intensity;
        // attenuation
        float distance = length(spotLight.Position - FragPos);
        float attenuation = 1.0 / (spotLight.ConstantAttenuation + spotLight.LinearAttenuation * distance + spotLight.QuadraticAttenuation * distance * distance);
        diffuse *= attenuation;
        specular *= attenuation;
        return diffuse + specular;
    }
    else
    {
        return vec3(0.f, 0.f, 0.f);
    }
}


void main()
{             
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

    vec3 ViewDir = normalize(viewPos - FragPos);
    vec3 lighting;
    //vec3 lighting = Diffuse * 0.25f; // hard-coded ambient component
    for (int i = 0; i < DirLightNb; ++i)
        lighting += DirLightComputation(dirLights[i], FragPos, Normal, Diffuse, Specular, ViewDir);
    for (int i = 0; i < PointLightNb; ++i)
        lighting += PointLightComputation(pointLights[i], FragPos, Normal, Diffuse, Specular, ViewDir);
    for (int i = 0; i < SpotLightNb; ++i)
        lighting += SpotLightComputation(spotLights[i], FragPos, Normal, Diffuse, Specular, ViewDir);

    FragColor = vec4(lighting, 1.0);
}