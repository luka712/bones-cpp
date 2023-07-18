#ifndef BNS_DIRECTORY_HPP

#define BNS_DIRECTORY_HPP

#include <string>

namespace bns 
{
    struct Directory final 
    {
        private:
            std::string m_userCommonDir;

        public: 
        /**
         * @brief The constructor. 
         */
        Directory();

        /**
         * @brief The root (persistent) directory that stays same between different versions of app.
         * 
         * @return std::string 
         */
        std::string Root();

        /**
         * @brief The common (persistent) directory that stays same between different versions of app.
 * 
         * @return std::string
         */
        std::string Common();

        /**
         * @brief Directory for user data that is common across revisions of a snap.
         * 
         * @return std::string
         */
        std::string UserCommon();

        /**
         * @brief Directory for user data that is common across revisions of a snap. 
         */
        void SetUserCommonDirectory(std::string dir);
    };
}

#endif // !BNS_DIRECTORY_HPP