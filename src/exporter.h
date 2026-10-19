#pragma once

#include "github_types.h"

#include <filesystem>
#include <vector>

void report_repositories(
    const std::vector<Repository>& repositories, const std::filesystem::path& output_path);
void export_repositories(
    const std::vector<Repository>& repositories, const std::filesystem::path& path);
