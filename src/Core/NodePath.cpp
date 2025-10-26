#include "./NodePath.h"

NodePath::NodePath()
{

};

NodePath::NodePath(std::shared_ptr<DependencyNode> node)
: NodePath()
{
    appendNode(node);
}

std::shared_ptr<DependencyNode> NodePath::getNodeFromIndex(size_t index) const
{
    if(index>=nodes_.size())
    {
        return nullptr;
    }
    return nodes_[index];
}

size_t NodePath::getSize() const
{
    return nodes_.size();

}

std::ostream &operator<<(std::ostream& out, const NodePath& nodePath)
{
    for(std::shared_ptr<DependencyNode> node : nodePath)
    {
        out << "/" << node->getFileStem();
    }
    return out;
}

void NodePath::appendNode(std::shared_ptr<DependencyNode> node)
{
    nodes_.push_back(node);
}

NodePath NodePath::appendNode(std::shared_ptr<DependencyNode> node) const
{
    NodePath newPath = *this;
    newPath.appendNode(node);
    return newPath;
}

std::shared_ptr<DependencyNode> NodePath::popNode()
{
    if(nodes_.size()<1)
    {
        return nullptr;
    }

    std::shared_ptr<DependencyNode> node = removeNode(getSize()-1);
    
    return node;
}

NodePath NodePath::popNode() const
{
    NodePath newPath = *this;
    newPath.popNode();
    return newPath;
}

std::shared_ptr<DependencyNode> NodePath::removeNode(size_t index)
{
    if(index>=nodes_.size())
    {
        return nullptr;
    }

    auto it = nodes_.begin()+index;
    std::shared_ptr<DependencyNode> node = *it;

    nodes_.erase(it);
    
    return node;
}

NodePath NodePath::removeNode(size_t index) const
{
    NodePath newPath = *this;
    newPath.removeNode(index);
    return newPath;
}

bool NodePath::hasRootNode() const
{
    return getSize() > 0;
}

std::shared_ptr<DependencyNode> NodePath::getRootNode() const
{
    return getNodeFromIndex(0);
}

std::shared_ptr<DependencyNode> NodePath::getLeafNode() const
{
    return getNodeFromIndex(getSize()-1);
}

void NodePath::setRootNode(std::shared_ptr<DependencyNode>)
{

}
