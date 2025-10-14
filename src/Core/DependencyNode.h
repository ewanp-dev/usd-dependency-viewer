#pragma once
#include <string>
#include <vector>

class DependencyNode
{
    public:
        DependencyNode(std::string filePath);
        std::string getFilePath();
        void addChildNode(DependencyNode* childNode);
        const std::vector<DependencyNode*>& getChildNodes() const;
        size_t getNumChildren() const;
    private:
        std::string filePath_;
        std::vector<DependencyNode*> childrenNodes_;
};
