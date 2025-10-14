#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Core/DependencyNode.h"

class UsdDependencyGraph
{
    public:
        UsdDependencyGraph(std::string usdFilePath);
        void printDebug();
    private:
        DependencyNode* createNode(std::string usdFilePath);
        
        // using ChildList = std::vector<std::vector<size_t>>;
        // ChildList nodeConnections_;
        std::vector<DependencyNode*> nodesStore_;
        std::unordered_map<std::string, DependencyNode*> pathNodeMap_;
        // std::set<DependencyNode*> nodesSet_;
        void walkTreeRecursive(std::string startNode);
};
    
