#pragma once 

#include <string>
#include <vector>

// This header file contains some debugging functions
// for the dependency graph class and potentially some other
// classes. This is purely for internal use for now

namespace dvCore
{
    struct UsdDebug 
    {
        public:
            void writeVectorToFile(const std::string& fileName, const std::vector<std::string>& inputVector);
            std::string getFileExtension(const std::string& filePath);
            bool fileExists(const std::string& filePath);
    };

}

