#pragma once 

#include <string>
#include <vector>
#include <memory>
#include <pxr/usd/sdf/layer.h>
#include <pxr/usd/sdf/layerUtils.h>

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
        pxr::SdfLayerRefPtr asSdf();
        std::string getDateModifiedTime();
        void setFavourite(bool condition);
        bool isFavourite();
        void setActive(bool condition = true);
        bool isActive();

    private:
        std::string filePath_;
        std::vector<std::shared_ptr<DependencyNode>> childrenNodes_;

        bool isFavourite_;
        bool isActive_;
};
