#if USE_D3D11 

#include "util/D3D11BlobUtil.hpp"
#include <exception>
#include <stdexcept>

namespace bns
{
    CComPtr<ID3DBlob> D3D11BlobUtil::CompileFromFile(std::string filePath, std::string d3d11ShaderModel, std::string entryPoint)
    {
        if (filePath.empty())
        {
            throw std::invalid_argument("D3D11BlobUtil::CompileFromFile: File path is empty.");
        }

        if (d3d11ShaderModel.empty())
        {
            throw std::invalid_argument("D3D11BlobUtil::CompileFromFile: Shader model is empty.");
        }

        if (entryPoint.empty())
        {
            throw std::invalid_argument("D3D11BlobUtil::CompileFromFile: Entry point is empty.");
        }

        // Must be vertex shader, pixel shader, compute shader or geometry shader. TODO: Add more shader types.
        if (!(
                d3d11ShaderModel == "vs_5_0" ||
                d3d11ShaderModel == "ps_5_0" ||
                d3d11ShaderModel == "cs_5_0" ||
                d3d11ShaderModel == "gs_5_0"))
        {
            std::string msg = "D3D11BlobUtil::CompileFromFile: Unknown shader model " + d3d11ShaderModel + ".";
            throw std::exception(msg.c_str());
        }

        // Define shader compilation flags
        DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS; // You can customize these flags

        CComPtr<ID3DBlob> shaderBlob = nullptr;
        CComPtr<ID3DBlob> errorBlob = nullptr;

        // Convert the file name to a wide string
        std::wstring wStr = std::wstring(filePath.begin(), filePath.end());

        // Compile the shader from the file
        HRESULT hr = D3DCompileFromFile(
            wStr.c_str(),             // Path to your HLSL file
            nullptr,                  // Optional defines
            nullptr,                  // Optional include files
            entryPoint.c_str(),       // Entry point function name
            d3d11ShaderModel.c_str(), // Shader model (e.g., "vs_5_0" for vertex shader)
            shaderFlags,              // Compilation flags
            0,                        // Effect flags (not used for standalone shader compilation)
            &shaderBlob,              // Output compiled shader bytecode
            &errorBlob                // Output error messages (if any)
        );

        if (FAILED(hr))
        {
            if (errorBlob)
            {
                std::string errorMsg = "D3D11BlobUtil::CompileFromFile: Failed to compile shader " + filePath + ". Error message: " + (char *)errorBlob->GetBufferPointer();
                throw std::exception(errorMsg.c_str());
            }
            else
            {
                std::string errorMsg = "D3D11BlobUtil::CompileFromFile: Failed to compile shader " + filePath + ".";
                throw std::exception(errorMsg.c_str());
            }
        }

        return shaderBlob;
    }
}


#endif 