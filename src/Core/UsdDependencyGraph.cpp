#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <pxr/usd/sdf/layer.h>
#include <pxr/usd/sdf/layerUtils.h>
#include <pxr/usd/ar/resolver.h>
#include <pxr/usd/ar/resolverContextBinder.h>
#include <pxr/usd/ar/resolverScopedCache.h>
#include "Core/UsdDependencyGraph.h"
#include "Core/DependencyNode.h"
#include <QFileDialog>

UsdDependencyGraph::UsdDependencyGraph(std::string usdFilePath)
{
    pxr::ArResolverScopedCache cache; // caches resolves while within scope

    rootNode_ = createNode(usdFilePath);
    walkTreeRecursive(usdFilePath);

    // printDebug();
}

std::shared_ptr<UsdDependencyGraph> UsdDependencyGraph::fromFileDialog()
{
    QFileDialog* dialog = new QFileDialog();
    // dialog->show();
    QUrl url = dialog->getOpenFileUrl();
    std::cout << "url: " << url.path().toStdString() << "\n";
    return std::make_shared<UsdDependencyGraph>(url.path().toStdString());
}


std::shared_ptr<DependencyNode> UsdDependencyGraph::getRootNode()
{
    return rootNode_;
}

void UsdDependencyGraph::printDebug()
{
    std::cout << "\n\n\n\n\n\n---------------------\n";
    std::cout << "Node store:\n";
    for(auto node : nodesStore_)
    {
        if(node->getNumChildren()==0) continue;

        std::cout << node->getFilePath() << " -> \n";

        for(auto childNode : node->getChildNodes())
        {
            std::cout << "\t" << childNode->getFilePath() << "\n";
        }
    }

}
    
std::shared_ptr<DependencyNode> UsdDependencyGraph::createNode(std::string usdFilePath)
{
    // check if node already exists
    auto it = pathNodeMap_.find(usdFilePath);
    const bool nodeExists = it != pathNodeMap_.end();
    if (nodeExists)
    {
        // std::cout << "returning node: " << it->second->getFilePath() << "\n";
        return it->second;
    }

    std::shared_ptr<DependencyNode> newNode = std::make_shared<DependencyNode>(usdFilePath);
    nodesStore_.push_back(newNode);
    pathNodeMap_[usdFilePath] = newNode;

    return newNode;
}

void UsdDependencyGraph::walkTreeRecursive(std::string startPath)
{
    if (std::find(pathsStore_.begin(), pathsStore_.end(), startPath) == pathsStore_.end())
    {
        pathsStore_.push_back(startPath);
    }

    pxr::SdfLayerRefPtr layer = pxr::SdfLayer::FindOrOpen(startPath);

    // temp band aid solution for resolving usdc -> usd
    if(!layer)
    {
        startPath = startPath.substr(0, startPath.size()-1);
        layer = pxr::SdfLayer::FindOrOpen(startPath);
    }

    if(!layer)
    {
        std::cout<<"Failed to open file: " << startPath << "\n";
        return;
    }

    std::shared_ptr<DependencyNode> startNode = createNode(startPath);

    std::string resolvedPath = layer->GetResolvedPath();

    std::set<std::string> externalReferences = layer->GetExternalReferences();


    for(auto reference : externalReferences)
    {
        std::string resolvedSubPath = pxr::SdfComputeAssetPathRelativeToLayer(layer, reference);

        std::shared_ptr<DependencyNode> childNode = createNode(resolvedSubPath);
        startNode->addChildNode(childNode);

        // std::cout << startPath << " -> " << resolvedSubPath << "\n";
        walkTreeRecursive(resolvedSubPath);
    }
}

std::vector<std::string> UsdDependencyGraph::getFlattenedPaths()
{
    return pathsStore_;
}

void oldCode(std::string usdFilePath){
    
    std::cout << "file path: " << usdFilePath << "\n";
    pxr::SdfLayerRefPtr layer = pxr::SdfLayer::FindOrOpen(usdFilePath);
    if(!layer)
    {
        std::cout<<"FAILED\n";
    }

    // pxr::ArResolver& resolver = pxr::ArGetResolver();

    std::string resolvedPath = layer->GetResolvedPath();

    std::set<std::string> externalReferences = layer->GetExternalReferences();
    // TODO: EXPLORE layer->GetSubLayerPaths()

    // pxr::ArResolverContext context = resolver.CreateDefaultContextForAsset(resolvedPath);
    // pxr::ArResolverContextBinder contextBinder(context); // uses context while in scope

    pxr::ArResolverScopedCache cache; // caches resolves while within scope

    for(auto reference : externalReferences)
    {
        std::string resolvedSubPath = pxr::SdfComputeAssetPathRelativeToLayer(layer, reference);
        // std::string identifier  = resolver.CreateIdentifier(reference);
        // std::cout << "reference: " << reference << "\n";
        // std::cout << "identifier: " << identifier << "\n";
        // std::string resolvedSubPath = resolver.Resolve(identifier);
        std::cout << "resolvedSubPath: " << resolvedSubPath << "\n";
        // constructDependencyTree(resolvedSubPath);
        // pxr::SdfLayerRefPtr layerNew = pxr::SdfLayer::FindOrOpen(resolvedSubPath);
        // std::cout << "layerNew: " << layerNew << "\n";
    }

}
