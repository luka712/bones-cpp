struct VSResult
{
    @builtin(position) Position: vec4<f32>,
    @location(0) v_texCoords: vec2<f32>,
    @location(1) v_tintColor: vec4<f32>
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
    return out;
}

// group 1, updated for each instance, texture.
@group(1) @binding(0)
var u_sampler: sampler;
@group(1) @binding(1)
var u_texture: texture_2d<f32>; 

struct FSResult
{
    @location(0) FragColor: vec4<f32>,
    @location(1) FragBrightness: vec4<f32>
};

@fragment
fn fs_main(@location(0) v_texCoords: vec2<f32>, @location(1) v_tintColor: vec4<f32>) -> FSResult 
{
    var out: FSResult;
    out.FragColor = textureSample(u_texture, u_sampler, v_texCoords) * v_tintColor;

    var l = dot(out.FragColor.rgb, vec3<f32>(0.2126, 0.7152, 0.0722));

    // TODO: move to buffer variable
    if(l > 0.4)
    {
        out.FragBrightness = out.FragColor;
    }
    else 
    {
        out.FragBrightness = vec4<f32>(0.0, 0.0, 0.0, out.FragColor.a);
    }

    return out;
}