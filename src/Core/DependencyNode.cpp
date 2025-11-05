#include "Core/DependencyNode.h"
#include <filesystem>

DependencyNode::DependencyNode(std::string filePath)
: filePath_{filePath}
{

}

void DependencyNode::addChildNode(std::shared_ptr<DependencyNode> childNode)
{
    childrenNodes_.push_back(childNode);
}

std::shared_ptr<DependencyNode> DependencyNode::getChildNode(size_t index)
{
    return childrenNodes_.at(index);
}

size_t DependencyNode::getNumChildren() const
{
    return childrenNodes_.size();
}

const std::vector<std::shared_ptr<DependencyNode>>& DependencyNode::getChildNodes() const
{
    return childrenNodes_;
}

std::string DependencyNode::getFilePath()
{
    return filePath_;
}

std::string DependencyNode::getFileName()
{
    // TODO: cache file name, maybe lazy evaluate
    // TODO: os specific delimeter. Maybe use a file library
    return std::filesystem::path(filePath_).filename();
}

std::string DependencyNode::getFileStem()
{
    return std::filesystem::path(filePath_).stem();
}

std::ostream& operator<<(std::ostream stream, DependencyNode& node)
{
    stream << node.getFileName();
    return stream;
}

