#if USE_METAL

#include "util/bns_metal_library_util.hpp"
#include <stdexcept>
#include "bns_types.hpp"

namespace bns
{

    MTL::Library *MetalLibraryUtil::Create(MTL::Device *device, std::string shaderSource, std::string label)
    {
        NS::Error *pError = nullptr;
        NS::String *nsSourceCode = NS::String::string(shaderSource.c_str(), NS::StringEncoding::UTF8StringEncoding);
        NS::String *nsLabel = NS::String::string(label.c_str(), NS::StringEncoding::UTF8StringEncoding);

        // Create library and set label.
        MTL::Library *pLibrary = device->newLibrary(nsSourceCode, nullptr, &pError);
        if (!pLibrary)
        {
            std::string libraryError = pError->localizedDescription()->utf8String();
            std::string msg = "MetalLibraryUtil::Create: Failed to create library. Error: " + libraryError + ".";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        pLibrary->setLabel(nsLabel);

        nsSourceCode->release();
        nsLabel->release();

        return pLibrary;
    }

}

#endif // __APPLE__
