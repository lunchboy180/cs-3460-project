#include "github_client.h"

#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include <httplib.h>

namespace {
std::string encode_query_component(const std::string& value) {
    constexpr char hex_digits[] = "0123456789ABCDEF";
    std::string encoded;

    for (unsigned char character : value) {
        if (std::isalnum(character) || character == '-' || character == '_' ||
            character == '.' || character == '~') {
            encoded += static_cast<char>(character);
        } else {
            encoded += '%';
            encoded += hex_digits[character >> 4];
            encoded += hex_digits[character & 0x0F];
        }
    }

    return encoded;
}
}

std::vector<std::string>
GitHubClient::search_pages(const SearchOptions& options) const {
    httplib::Client client("https://api.github.com");

    std::string path =
        "/search/repositories?q=" +
        encode_query_component(options.query) +
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