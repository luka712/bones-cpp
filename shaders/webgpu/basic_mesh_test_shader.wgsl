struct VertexOut {
    @builtin(position) position: vec4f,
    @location(0) color: vec4f,
}

@vertex 
fn vs_main(
    @location(0) pos: vec3f,  // xyz
    @location(1) color: vec4f,  // rgbw
) -> VertexOut 
{ 
   
    var output : VertexOut; 

    output.position = vec4f(pos, 1.0);
    output.color = color;

    return output;
}


@fragment
fn fs_main(fragData: VertexOut ) -> @location(0) vec4f 
{
    return fragData.color;
}
