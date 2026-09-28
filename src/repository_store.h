#pragma once

#include "github_types.h"

#include <string>
#include <vector>

class RepositoryStore {
public:
    void print(const std::vector<Repository>& repositories) const;
    void save(const std::vector<Repository>& repositories, const std::string& path) const;
};