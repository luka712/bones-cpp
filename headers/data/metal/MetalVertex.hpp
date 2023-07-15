#ifndef BNS_METAL_VERTEX_HPP

#define BNS_METAL_VERTEX_HPP

namespace bns
{
    /**
     * @brief The Metal vertex P3C4 struct.
     * The Metal vertex P3C4 struct is used to describe the vertex.
     * The P3 stands for position of 3 floats.
     * The C4 stands for color of 4 floats.
    */
    struct MetalVertexP3C4
    {
        float position[3];
        float color[4];
    };
}

#endif 