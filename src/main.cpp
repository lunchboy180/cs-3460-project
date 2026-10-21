#include "github_client.h"
#include "data_loader.h"
#include "exporter.h"
#include "repository_parser.h"
#include "repository_analyzer.h"
#include "repository_store.h"

#include <filesystem>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
std::uint64_t parse_unsigned(const std::string& text, const std::string& name) {
    if (text.empty() || text.front() == '-') {
        throw std::invalid_argument(name + " must be a non-negative integer");
    }
    std::size_t parsed_characters = 0;
    const auto value = std::stoull(text, &parsed_characters);
    if (parsed_characters != text.size()) {
        throw std::invalid_argument(name + " must be a non-negative integer");
    }
    return value;
}

int run_slither(int argc, char* argv[]) {
    SearchOptions options;
    options.query = argc > 2 ? argv[2] : "stars:>=0";
    if (argc > 3) {
        const auto count = parse_unsigned(argv[3], "count");
        if (count == 0 || count > std::numeric_limits<std::size_t>::max()) {
            throw std::invalid_argument("count must be a positive integer");
        }
        options.count = static_cast<std::size_t>(count);
    }

    GitHubClient client;
    RepositoryParser parser;
    RepositoryStore store;
    const auto repositories = parser.parse(client.search_pages(options));
    store.print(repositories);
    store.save(repositories, "repositories.json");
    std::cout << "Collected " << repositories.size() << " repositories for query \""
              << options.query << "\"." << std::endl;
    return 0;
}

int run_analysis(int argc, char* argv[]) {
    std::filesystem::path input_path = "repositories.json";
    std::filesystem::path output_path = "selected.json";
    AnalysisOptions options;

    for (int index = 1; index < argc; ++index) {
        const std::string argument = argv[index];
        auto require_value = [&](const std::string& option) {
            if (index + 1 >= argc) {
                throw std::invalid_argument(option + " requires a value");
            }
            return std::string(argv[++index]);
        };
        if (argument == "--min-stars") {
            options.min_stars = parse_unsigned(require_value(argument), "min-stars");
        } else if (argument == "--language") {
            options.language = require_value(argument);
        } else if (argument == "--sort") {
            options.sort_key = require_value(argument);
        } else if (argument == "--top-n") {
            const auto top_n = parse_unsigned(require_value(argument), "top-n");
            if (top_n > std::numeric_limits<std::size_t>::max()) {
                throw std::invalid_argument("top-n is too large");
            }
            options.top_n = static_cast<std::size_t>(top_n);
        } else if (argument == "--help") {
            std::cout << "Usage: Slitherer "
                         "[--min-stars n] [--language name] "
                         "[--sort stars|forks|updated] [--top-n n]\n"
                         "       Slitherer --slither [query] [count]\n";
            return 0;
        } else {
            throw std::invalid_argument("unknown option: " + argument);
        }
    }

    const auto repositories = load_repositories(input_path);
    const auto selected = filter_repositories(repositories, options);
    const auto sorted = sort_repositories(selected, options);
    std::cout << "Dataset: " << input_path.string() << '\n';
    std::cout << "Repositories loaded: " << repositories.size() << '\n';
    std::cout << "Filter: stars >= " << options.min_stars << '\n';
    std::cout << "Language: " << (options.language.empty() ? "any" : options.language) << '\n';
    std::cout << "Sort: " << options.sort_key << " (descending)\n";
    std::cout << "Top N: " << options.top_n << '\n';
    export_repositories(sorted, output_path);
    report_repositories(sorted, output_path);
    return 0;
}
}

int main(int argc, char* argv[]) {
    try {
        if (argc > 1 && std::string(argv[1]) == "--slither") {
            return run_slither(argc, argv);
        }
        return run_analysis(argc, argv);
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }
}
