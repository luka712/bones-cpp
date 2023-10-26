#define FORWARD_2D_NUM_OF_POINT_LIGHTS ##FORWARD_2D_NUM_OF_POINT_LIGHTS##

struct VSResult
{
    @builtin(position) Position: vec4f,
    @location(0) v_texCoords: vec2f,
    @location(1) v_tintColor: vec4f,
    @location(2) v_worldPos: vec3f // need fragment position in world space for lighting
};

struct AmbientLight 
{
    color: vec4f,
    intensity: f32 
};

struct PointLight 
{
    color: vec4f, // 12b 
    position: vec3f, // 24b
    intensity: f32,  
    attenuationUnit: f32,
    attenuationConstant: f32, 
    attenuationLinear: f32, // 48b 
    attenuationQuadratic: f32
};

 // group 0, update once per pass 
 @group(0) @binding(0)
 var<uniform> u_projectionViewMatrix: mat4x4<f32>;

@vertex
fn vs_main(@location(0) a_vertex: vec3<f32>,
           @location(1) a_texCoords: vec2<f32>,
           @location(2) a_tintColor: vec4<f32>) -> VSResult 
{
    var out: VSResult;
    out.Position = u_projectionViewMatrix * vec4<f32>(a_vertex, 1.0);
    out.v_texCoords = a_texCoords;
    out.v_tintColor = a_tintColor;
    out.v_worldPos = a_vertex;
    return out;
}

// group 1, updated for each instance, texture.
@group(1) @binding(0)
var u_sampler: sampler;
@group(1) @binding(1)
var u_texture: texture_2d<f32>; 

@group(2) @binding(0) var<uniform> u_brightnessThreshold: f32;
@group(2) @binding(1) var<uniform> u_ambientLight: AmbientLight; 
@group(2) @binding(2) var<uniform> u_pointLights: array<PointLight,FORWARD_2D_NUM_OF_POINT_LIGHTS>;

fn point_light(light: PointLight, worldPos: vec3f) -> vec3f
{
    // Normal is always same for a sprite
    var normal = vec3f(0.0, 0.0, 1.0);
    var lightDir = light.position - worldPos;
    var distance = length(lightDir);
    lightDir = normalize(lightDir);

    var u = light.attenuationUnit;
    var c = light.attenuationConstant;
    var l = light.attenuationLinear * distance;
    var q = light.attenuationQuadratic * (distance * distance);

    var attenuation = u / (c + l + q);
    var diffuse = max(dot(normal, lightDir), 0.0);

    return diffuse * light.color.rgb * light.intensity * attenuation;
}

struct FSResult
{
    @location(0) FragColor: vec4f,
    @location(1) FragBrightness: vec4f
};

@fragment
fn fs_main(
     @location(0) v_texCoords: vec2f,
     @location(1) v_tintColor: vec4f,
     @location(2) v_worldPos: vec3f) -> FSResult 
{
    var ambient = u_ambientLight.color.rgb * u_ambientLight.intensity;

    var point = vec3f(0.0);
    for(var i = 0; i < FORWARD_2D_NUM_OF_POINT_LIGHTS; i++)
    {
        point += point_light(u_pointLights[i], v_worldPos);
    }

    var out: FSResult;
    var fragColor = textureSample(u_texture, u_sampler, v_texCoords) * v_tintColor;
    out.FragColor = vec4f(fragColor.rgb, fragColor.a);
    out.FragColor *= vec4f(ambient + point, 1.0);

    var l = dot(out.FragColor.rgb, vec3<f32>(0.299, 0.587, 0.114));
    if(l > u_brightnessThreshold)
    {
        out.FragBrightness = out.FragColor;
    }
    else 
    {
        out.FragBrightness = vec4<f32>(0.0, 0.0, 0.0, out.FragColor.a);
    }

    return out;
}