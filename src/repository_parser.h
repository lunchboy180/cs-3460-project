#pragma once

#include "github_types.h"

#include <string>
#include <vector>

class RepositoryParser {
public:
    std::vector<Repository> parse(const std::vector<std::string>& json_items) const;
};