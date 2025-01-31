
// Copyright (c) 2025+ Vicen-te
// This code is released under the MIT License.

// Header
#include "LabelLoader.hpp"

// C++
#include <iostream>
#include <fstream>
#include <stdexcept>


bool LabelLoader::Load(const std::string& file_path)
{
    // Clear the list in case it's being reloaded
    class_list->clear();

    // Open the file
    std::ifstream ifs(file_path);
    if (!ifs.is_open())
    {
        std::cerr << "Error opening the file: " << file_path << std::endl;
        return false;
    }

    std::string line;
    // Read each line from the file
    while (getline(ifs, line))
    {
        // Add each class to the list
        class_list->push_back(line);
    }

    // Check if any data was loaded
    if (class_list->empty())
    {
        std::cerr << "The file is empty or contains no classes." << std::endl;
        return false;
    }

    return true;
}