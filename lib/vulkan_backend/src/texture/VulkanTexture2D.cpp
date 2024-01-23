#if USE_VULKAN

#include "texture/VulkanTexture2D.hpp"
#include "VulkanUtil.hpp"

namespace bns
{
    VulkanTexture2D::VulkanTexture2D(const VkPhysicalDevice &physicalDevice,
                                     const VkDevice &device,
                                     const VkCommandPool &commandPool,
                                     const VkQueue &graphicsQueue,
                                     ImageData *imageData, i32 textureUsageFlags, TextureFormat format)
        : Texture2D(imageData->Width, imageData->Height, textureUsageFlags, format),
          m_physicalDevice(physicalDevice), m_device(device), m_commandPool(commandPool), m_graphicsQueue(graphicsQueue)
    {
        m_imageData = imageData;
        m_textureUsageFlags = textureUsageFlags;
        m_format = format;
    }

    VulkanTexture2D::~VulkanTexture2D()
    {
        Release();
    }

    void VulkanTexture2D::Initialize()
    {
        // For staging buffer, we need to create a buffer and allocate memory for it.
        // Then we copy texture data to the buffer, and use it to create texture.
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;

        stagingBuffer = VulkanUtil::Buffer.CreateStagingBuffer(
            m_physicalDevice,
            m_device,
            m_imageData->GetSize(),
            &stagingBufferMemory);

        // Copy texture data to staging buffer.
        VulkanUtil::DeviceMemory.Map(m_device, stagingBufferMemory, m_imageData->Data, m_imageData->GetSize());

        // Create texture.
        m_image = VulkanUtil::Image.Create(
            m_physicalDevice,
            m_device,
            m_imageData->Width,
            m_imageData->Height,
            &m_imageMemory);

        // Copy staging buffer to texture.
        // Involes two steps:
        // 1. Transition image layout to VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL.
        // 2. Copy buffer to image.
        VulkanUtil::ImageLayout.TransitionImageLayout(
            m_device,
            m_commandPool,
            m_graphicsQueue,
            m_image,
            VK_FORMAT_R8G8B8A8_SRGB,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        VulkanUtil::Buffer.CopyBufferToImage(
            m_device,
            m_commandPool,
            m_graphicsQueue,
            stagingBuffer,
            m_image,
            m_imageData->Width,
            m_imageData->Height);

        // To be able to sample the texture, we need to transition the image layout to VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL.
        VulkanUtil::ImageLayout.TransitionImageLayout(
            m_device,
            m_commandPool,
            m_graphicsQueue,
            m_image,
            VK_FORMAT_R8G8B8A8_SRGB,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    }

    void VulkanTexture2D::Release()
    {
        if (m_image != VK_NULL_HANDLE)
        {
            vkDestroyImage(m_device, m_image, nullptr);
            m_image = VK_NULL_HANDLE;
        }

        if (m_imageMemory != VK_NULL_HANDLE)
        {
            vkFreeMemory(m_device, m_imageMemory, nullptr);
            m_imageMemory = VK_NULL_HANDLE;
        }
    }
}

#endif