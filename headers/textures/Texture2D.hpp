#ifndef BNS_TEXTURE_2D_HPP

#define BNS_TEXTURE_2D_HPP

#include "data/Types.hpp"

namespace bns 
{
    class Texture2D
    {
    protected:
        u32 m_id;

        /**
         * The id generator for the textures. Is increased whenever a new texture is created.
        */
        static u32 s_idGenerator;

        /**
         * @brief Generates a new id for the texture.
         */
        static u32 GenerateID();

    public:
        Texture2D();

        /**
         * @brief The id of the texture.
        */
        inline u32 GetID() const { return m_id; }

        /**
         * @brief Initialize the texture.
        */
        virtual void Initialize() = 0;
    };
}

#endif 