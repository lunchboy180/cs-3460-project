#include "repository_analyzer.h"
#include "github_types.h"

#include <nlohmann/json.hpp>

#include <iostream>
#include <utility>

bool matches_filters(const Repository& r,
                     const AnalysisOptions& options) {
    if (r.stars < options.min_stars) {
        return false;
    }
    if (!options.language.empty() &&
        r.language != options.language) {
        return false;
    }
    return true;
}

std::vector<Repository>
filter_repositories(const std::vector<Repository>& input,
                    const AnalysisOptions& options) {
    std::vector<Repository> result;
    for (const Repository& r : input) {
        if (matches_filters(r, options)) {
            result.push_back(r);
        }
    }
    return result;
}

bool compare_by_stars(const Repository& a, const Repository& b) {
    if (a.stars != b.stars) {
        return a.stars > b.stars;
    }
    if (a.owner != b.owner) {
        return a.owner < b.owner;
    }
    return a.name < b.name;
}

bool compare_by_forks(const Repository& a, const Repository& b) {
    if (a.forks != b.forks) {
        return a.forks > b.forks;
    }
    if (a.owner != b.owner) {
        return a.owner < b.owner;
    }
    return a.name < b.name;
}

bool compare_by_updated(const Repository& a, const Repository& b) {
    if (a.updated_at != b.updated_at) {
        return a.updated_at > b.updated_at;
    }
    if (a.owner != b.owner) {
        return a.owner < b.owner;
    }
    return a.name < b.name;
}

std::vector<Repository>
sort_repositories(const std::vector<Repository>& input,
                       const AnalysisOptions& options) {
    std::vector<Repository> rows = input;
    if (options.sort_key == "stars") {
        std::sort(rows.begin(), rows.end(), compare_by_stars);
    }
    else if (options.sort_key == "forks") {
        std::sort(rows.begin(), rows.end(), compare_by_forks);
    }
    else if (options.sort_key == "updated") {
        std::sort(rows.begin(), rows.end(), compare_by_updated);
    }
    if (rows.size() > options.top_n) {
        rows.resize(options.top_n);
    }
    return rows;
}
