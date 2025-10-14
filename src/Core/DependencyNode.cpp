#include "Core/DependencyNode.h"

DependencyNode::DependencyNode(std::string filePath)
: filePath_{filePath}
{

}

void DependencyNode::addChildNode(DependencyNode* childNode)
{
    childrenNodes_.push_back(childNode);
}

size_t DependencyNode::getNumChildren() const
{
    return childrenNodes_.size();
}

const std::vector<DependencyNode*>& DependencyNode::getChildNodes() const
{
    return childrenNodes_;
}

std::string DependencyNode::getFilePath()
{
    return filePath_;
}
