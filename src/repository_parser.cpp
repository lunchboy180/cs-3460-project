#include "repository_parser.h"

#include <nlohmann/json.hpp>
#include <utility>

using json = nlohmann::json;

std::vector<Repository>
RepositoryParser::parse(const std::vector<std::string>& json_items) const {
    std::vector<Repository> repos;

    for (const auto& body : json_items) {
        const auto root = json::parse(body);
        for (const auto& item : root.at("items")) {
            Repository repository;
            repository.owner = item.at("owner").at("login").get<std::string>();
            repository.name = item.at("name").get<std::string>();
            repository.description = item.at("description").is_null()
                ? "" : item.at("description").get<std::string>();
            repository.stars = item.at("stargazers_count").get<std::uint64_t>();
            repository.forks = item.at("forks_count").get<std::uint64_t>();
            repository.language = item.at("language").is_null()
                ? "" : item.at("language").get<std::string>();
            repository.size = item.at("size").get<std::uint64_t>();
            repository.updated_at = item.at("updated_at").get<std::string>();
            repository.url = item.at("html_url").get<std::string>();
            repos.push_back(std::move(repository));
        }
    }

    return repos;
}