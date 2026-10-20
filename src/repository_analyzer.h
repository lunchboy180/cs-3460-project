#pragma once

#include "github_types.h"

#include <filesystem>
#include <vector>

bool matches_filters(const Repository& r, const AnalysisOptions& options);
std::vector<Repository> filter_repositories(const std::vector<Repository>& input, const AnalysisOptions& options);
bool compare_by_stars(const Repository& a, const Repository& b);
bool compare_by_forks(const Repository& a, const Repository& b);
bool compare_by_updated(const Repository& a, const Repository& b);
