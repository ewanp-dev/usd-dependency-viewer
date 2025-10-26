#pragma once
#include <string>
#include <vector>
#include <memory>

class DependencyNode
{
    public:
        DependencyNode(std::string filePath);
        std::string getFilePath();
        std::string getFileName();
        std::string getFileStem();

        void addChildNode(std::shared_ptr<DependencyNode> childNode);
        const std::vector<std::shared_ptr<DependencyNode>>& getChildNodes() const;
        size_t getNumChildren() const;
        std::shared_ptr<DependencyNode> getChildNode(size_t index);

    private:
        std::string filePath_;
        std::vector<std::shared_ptr<DependencyNode>> childrenNodes_;
};
