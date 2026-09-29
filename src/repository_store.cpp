#include "repository_store.h"

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <stdexcept>

void RepositoryStore::print(const std::vector<Repository>& repositories) const {
    for (const auto& repository : repositories) {
        std::cout << repository.owner << '/' << repository.name << " | " << repository.stars << " stars | "
                  << repository.forks << " forks | " << repository.language << " | "
                  << repository.size << " KB | " << repository.url << '\n';
    }
}

void RepositoryStore::save(const std::vector<Repository>& repositories, const std::string& path) const {
    nlohmann::json output = nlohmann::json::array();
    for (const auto& repository : repositories) {
        output.push_back(repository_to_json(repository));
    }

    std::ofstream output_file(path);
    if (!output_file) {
        throw std::runtime_error("Could not open output file: " + path);
    }
    output_file << output.dump(2) << '\n';
    if (!output_file) {
        throw std::runtime_error("Could not write output file: " + path);
    }
}