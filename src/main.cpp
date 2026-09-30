#include "github_client.h"
#include "repository_parser.h"
#include "repository_store.h"

#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[]) {
    try {
        SearchOptions options;
        options.query = "stars:>=0";

        if (argc > 3) {
            throw std::invalid_argument("usage: Slitherer [query] [count]");
        }
        if (argc > 1) {
            options.query = argv[1];
        }
        if (argc > 2) {
            const std::string count_text = argv[2];
            std::size_t parsed_characters = 0;
            const auto count = std::stoull(count_text, &parsed_characters);
            if (parsed_characters != count_text.size() || count == 0 ||
                count > std::numeric_limits<std::size_t>::max()) {
                throw std::invalid_argument("count must be a positive integer");
            }
            options.count = static_cast<std::size_t>(count);
        }

        GitHubClient client;
        RepositoryParser parser;
        RepositoryStore store;
        const auto response_pages = client.search_pages(options);
        const auto repositories = parser.parse(response_pages);
        store.print(repositories);
        store.save(repositories, "repositories.json");
        std::cout << "Collected " << repositories.size() << " repositories for query \""
                  << options.query << "\"." << std::endl;
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }
}