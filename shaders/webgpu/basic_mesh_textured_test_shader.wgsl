struct VertexOut {
    @builtin(position) position: vec4f,
    @location(0) texcoord: vec2f,
    @location(1) color: vec4f,
}

@vertex 
fn vs_main(
    @location(0) pos: vec3f,  // xyz
    @location(1) texcoord: vec2f,  // uv
    @location(2) color: vec4f,  // rgbw,

) -> VertexOut 
{ 
   
    var output : VertexOut; 

    output.position = vec4f(pos, 1.0);
    output.texcoord = texcoord;
    output.color = color;

    return output;
}

@group(0) @binding(0)
var uSampler: sampler;

@group(0) @binding(1) 
var uTexture: texture_2d<f32>;

@fragment
fn fs_main(fragData: VertexOut ) -> @location(0) vec4f 
{
    return textureSample(uTexture, uSampler,fragData.texcoord) * fragData.color;
}
