#include "github_client.h"

#include <cstdlib>
#include <string>
#include <vector>
#include <httplib.h>

std::vector<std::string>
GitHubClient::search_pages(const SearchOptions& options) const {
    httplib::Client client("https://api.github.com");

    std::string path =
        "/search/repositories?q=" +
        httplib::encode_uri_component(options.query) +
        "&per_page=" + std::to_string(options.count);

    httplib::Headers headers{
        {"Accept", "application/vnd.github+json"},
        {"X-GitHub-Api-Version", "2026-03-10"},
        {"User-Agent", "cs3460-github-crawler"}
    };
    if (const char* token = std::getenv("GITHUB_TOKEN")) {
        headers.emplace("Authorization", std::string("Bearer ") + token);
    }

    auto result = client.Get(path, headers);
    if (!result || result->status != 200) {
        return {};
    }

    return {result->body};
}