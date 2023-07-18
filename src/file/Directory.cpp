#include "file/Directory.hpp"
#include "Constants.hpp"

bns::Directory::Directory()
{
    m_userCommonDir = USER_COMMON_DIRECTORY;
}

std::string bns::Directory::Root()
{
    return std::string(ROOT_DIRECTORY);
}

std::string bns::Directory::Common()
{
    return std::string(COMMON_DIRECTORY);
}

std::string bns::Directory::UserCommon()
{
    return m_userCommonDir;
}

void bns::Directory::SetUserCommonDirectory(std::string val)
{
    m_userCommonDir = val;
}