#pragma once
#include "./DependencyNode.h"
#include <iostream>

class NodePath
{
    public:
        NodePath();
        NodePath(std::shared_ptr<DependencyNode> node);
        void appendNode(std::shared_ptr<DependencyNode> node);
        NodePath appendNode(std::shared_ptr<DependencyNode> node) const;

        std::shared_ptr<DependencyNode> popNode();
        NodePath popNode() const;

        std::shared_ptr<DependencyNode> removeNode(size_t index);
        NodePath removeNode(size_t index) const;

        std::shared_ptr<DependencyNode> getNodeFromIndex(size_t index) const;
        std::shared_ptr<DependencyNode> getRootNode() const;
        std::shared_ptr<DependencyNode> getLeafNode() const;
        bool hasRootNode() const;
        size_t getSize() const;
        void setRootNode(std::shared_ptr<DependencyNode>);

        friend std::ostream &operator<<(std::ostream& out, const NodePath& nodePath);

        auto begin() { return nodes_.begin(); }
        auto end() { return nodes_.end(); }
        auto begin() const { return nodes_.begin(); }
        auto end() const { return nodes_.end(); }
    private:
        std::vector<std::shared_ptr<DependencyNode>> nodes_;

};
