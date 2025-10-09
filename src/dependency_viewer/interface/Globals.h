#pragma once

#include <filesystem>
#include <string>

constexpr int DV_BUTTON_WIDTH = 25;
constexpr int DV_BUTTON_HEIGHT = 25;
const bool DV_ICONS_INVERTED = false;
const std::string DV_CURRENT_DIRECTORY = std::filesystem::current_path().string();
const std::string DV_ELEMENTS_DIRECTORY = DV_CURRENT_DIRECTORY + "/src/dependency_viewer/interface/elements/";

