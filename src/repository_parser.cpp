#include <nlohmann/json.hpp>
using json = nlohmann::json;

json root = json::parse(body);
std::vector<Repository> repos;
for (const auto& item : root.at("items")) {
    Repository r;
    r.owner = item.at("owner").at("login").get<std::string>();
    r.name = item.at("name").get<std::string>();
    r.description = item.at("description").is_null()
        ? "" : item.at("description").get<std::string>();
    r.stars = item.at("stargazers_count").get<std::uint64_t>();
    r.forks = item.at("forks_count").get<std::uint64_t>();
    r.language = item.at("language").is_null()
        ? "" : item.at("language").get<std::string>();
    r.size = item.at("size").get<std::uint64_t>();
    r.updated_at = item.at("updated_at").get<std::string>();
    r.url = item.at("html_url").get<std::string>();
    repos.push_back(std::move(r));
}