#pragma once

#include "github_types.h"

#include <string>
#include <vector>

class GitHubClient {
public:
    std::vector<std::string> search_pages(const SearchOptions& options) const;
};