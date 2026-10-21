#pragma once

#include "github_types.h"

#include <vector>

std::vector<Repository> filter_repositories(const std::vector<Repository>& input, const AnalysisOptions& options);
std::vector<Repository> sort_repositories(const std::vector<Repository>& input, const AnalysisOptions& options);
