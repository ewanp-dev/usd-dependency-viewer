#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Core/DependencyNode.h"
#include <memory>

class UsdDependencyGraph
{
    public:
        UsdDependencyGraph(std::string usdFilePath);
        static std::shared_ptr<UsdDependencyGraph> fromFileDialog();
        void printDebug();
        std::vector<std::string> getFlattenedPaths();
        std::shared_ptr<DependencyNode> getRootNode();
        
    private:
        std::shared_ptr<DependencyNode> createNode(std::string usdFilePath);
        void writeDependencies(const std::string& fileName);

        std::shared_ptr<DependencyNode> rootNode_;
        
        // using ChildList = std::vector<std::vector<size_t>>;
        // ChildList nodeConnections_;
        std::vector<std::shared_ptr<DependencyNode>> nodesStore_;
        std::vector<std::string> pathsStore_;
        std::unordered_map<std::string, std::shared_ptr<DependencyNode>> pathNodeMap_;
        // std::set<DependencyNode*> nodesSet_;
        void walkTreeRecursive(std::string startNode);
};
    
