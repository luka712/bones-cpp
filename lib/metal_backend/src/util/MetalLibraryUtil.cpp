#ifdef __APPLE__ 

#include "util/MetalLibraryUtil.hpp"

namespace bns
{

    MTL::Library *MetalLibraryUtil::Create(MTL::Device *device, std::string shaderSource)
    {
        NS::Error *pError = nullptr;
        NS::String *nsSourceCode = NS::String::string(shaderSource.c_str(), NS::StringEncoding::UTF8StringEncoding);
        MTL::Library *pLibrary = device->newLibrary(nsSourceCode, nullptr, &pError);
        if (!pLibrary)
        {
            printf("%s", pError->localizedDescription()->utf8String());
            assert(false);
        }

        nsSourceCode->release();

        return pLibrary;
    }

}

#endif // __APPLE__