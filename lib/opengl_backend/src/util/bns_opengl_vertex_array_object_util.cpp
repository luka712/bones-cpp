#if USE_OPENGL

#include "util/bns_opengl_vertex_array_object_util.hpp"
#include "bns_opengl_util.hpp"

namespace bns 
{
    GLuint OpenGLVertexArrayObjectUtil::Create(std::string label, bool unbind)
    {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        if (label != "")
        {
            glObjectLabel(GL_VERTEX_ARRAY, vao, label.size(), label.c_str());
        }
        if (unbind)
        {
            glBindVertexArray(0);
        }
        return vao;
    }

    GLuint OpenGLVertexArrayObjectUtil::Create(const std::vector<OpenGLBufferLayoutDescriptor> &descriptors, std::string label)
    {
        GLuint vao = Create(label, false);

        // Describe attributes
        u32 i = 0;
        for (const OpenGLBufferLayoutDescriptor& openGLBufferLayoutDescriptor: descriptors)
        {
            const BufferLayoutDescriptor& descriptor = openGLBufferLayoutDescriptor.BufferLayoutDescriptor;
            GLuint buffer = openGLBufferLayoutDescriptor.Buffer;
            
            // Bind buffer.
            glBindBuffer(GL_ARRAY_BUFFER, buffer);

            for (const BufferLayoutAttributeDescriptor& attribute: descriptor.Attributes)
            {
                size_t size = OpenGLUtil::Converter.Convert(attribute.Format);
                bool isInstanced = openGLBufferLayoutDescriptor.IsInstanced;

                // Enable and describe the attribute.
                glEnableVertexAttribArray(i);
                glVertexAttribPointer(i, size, GL_FLOAT, false, descriptor.Stride, (void*)attribute.Offset);

                if (isInstanced)
                {
                    glVertexAttribDivisor(i, 1);
                }
               
                i++;
            }
        }
        
        glBindVertexArray(0);
        return vao;
    }
}

#endif 