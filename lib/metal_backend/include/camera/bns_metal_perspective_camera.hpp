#if USE_METAL

#ifndef BNS_METAL_PERSPECTIVE_CAMERA_HPP

#define BNS_METAL_PERSPECTIVE_CAMERA_HPP

#include "camera/bns_perspective_camera.hpp"
#include "buffers/bns_metal_uniform_buffer.hpp"

namespace bns
{
    class MetalRenderer;

    /// @brief The perspective camera for Metal.
    class MetalPerspectiveCamera : public PerspectiveCamera
    {
    private:
        MetalRenderer *m_renderer;
        MTL::Device* m_device;
        MetalUniformBuffer<Mat4x4f> *m_buffer;

    public:
        /// @brief Constructor for the perspective camera.
        /// @param renderer The renderer.
        /// @param aspectRatio The aspect ratio of the camera.
        MetalPerspectiveCamera(Renderer *renderer, f32 aspectRatio);

        /// @brief Get the buffer of the camera.
        inline UniformBuffer<Mat4x4f> *GetBuffer() const
        {
            return m_buffer;
        }

        void Initialize() override;
        void Update() override;
        void Dispose() override;
    };
} // namespace bns

#endif // BNS_METAL_PERSPECTIVE_CAMERA_HPP

#endif 