#include "data_loader.h"

#include <nlohmann/json.hpp>

#include <fstream>
#include <stdexcept>
#include <utility>

std::vector<Repository>
load_repositories(const std::filesystem::path& path) {
    std::ifstream input(path);
    if (!input) {
        throw std::runtime_error("Cannot open repository dataset");
    }
    nlohmann::json root;
    input >> root;
    if (!root.is_array()) {
        throw std::runtime_error("Repository dataset must be a JSON array");
    }
    std::vector<Repository> repositories;
    for (const auto& item : root) {
        Repository r;
        r.owner = item.at("owner").get<std::string>();
        r.name = item.at("name").get<std::string>();
        r.description = item.at("description").get<std::string>();
        r.stars = item.at("stars").get<std::uint64_t>();
        r.forks = item.at("forks").get<std::uint64_t>();
        r.language = item.at("language").get<std::string>();
        r.size = item.at("size").get<std::uint64_t>();
        r.updated_at = item.at("updated_at").get<std::string>();
        r.url = item.at("url").get<std::string>();
        repositories.push_back(std::move(r));
    }
    return repositories;
}