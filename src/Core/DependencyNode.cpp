#include "Core/DependencyNode.h"
#include <filesystem>
// #include <chrono>
// #include <iomanip>
// #include <sstream>

DependencyNode::DependencyNode(std::string filePath)
: filePath_{filePath}
{
    isFavourite_ = false;
    setActive(false);
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

pxr::SdfLayerRefPtr DependencyNode::asSdf()
{
    return pxr::SdfLayer::FindOrOpen(filePath_);
}

std::string DependencyNode::getDateModifiedTime()
{
    if (!std::filesystem::exists(filePath_))
        return "FILE NOT FOUND!";

    auto ftime = std::filesystem::last_write_time(filePath_);

    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        ftime - std::filesystem::file_time_type::clock::now()
        + std::chrono::system_clock::now()
    );

    std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);

    std::tm tm{};
    localtime_r(&cftime, &tm);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

void DependencyNode::setFavourite(bool condition)
{
    isFavourite_ = condition;
}

bool DependencyNode::isFavourite()
{
    return isFavourite_;
}

void DependencyNode::setActive(bool condition)
{
    isActive_ = condition;
}

bool DependencyNode::isActive()
{
    return isActive_;
}

