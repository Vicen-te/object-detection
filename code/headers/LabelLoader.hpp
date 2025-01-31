
// Copyright (c) 2025+ Vicen-te
// This code is released under the MIT License.

#pragma once

// C++
#include <vector>
#include <string>
#include <memory>

class LabelLoader
{
private:
    // Shared pointer to hold the class names
    std::shared_ptr<std::vector<std::string>> class_list;

public:
    /**
     * Constructor for the LabelLoader class.
     * Initializes the object with an empty class list.
     */
    LabelLoader() : class_list(std::make_shared<std::vector<std::string>>()) {}

    /**
     * Loads class names from a text file into the internal shared pointer.
     * @param file_path The path to the file containing the class names (one class per line).
     * @return true if the file is loaded successfully, false in case of error.
     */
    bool Load(const std::string& file_path);

    /**
     * Gets the list of loaded class names.
     * @return A reference to the shared pointer to the list of loaded class names.
     */
    inline std::shared_ptr<std::vector<std::string>> GetClassList() const
    {
        return class_list;
    }

    /**
     * Checks if the class list is empty.
     * @return true if the class list is empty, false otherwise.
     */
    inline bool IsClassListEmpty() const
    {
        return class_list->empty();
    }

    /**
     * Gets the count of classes loaded.
     * @return The number of classes in the list.
     */
    inline size_t GetClassCount() const
    {
        return class_list->size();
    }
};
