#include "file_loader.h"
#include <fstream>
#include <streambuf>

std::string FileLoader::loadFile(std::string &filename)
{
    std::ifstream file(filename);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return str;
}
