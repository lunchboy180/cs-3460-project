#include "exporter.h"
#include "repository_store.h"

#include <iostream>

void report_repositories(
    const std::vector<Repository>& repositories, const std::filesystem::path& output_path) {
    std::cout << "OWNER/NAME STARS FORKS LANGUAGE UPDATED\n";
    for (const auto& repository : repositories) {
        std::cout << repository.owner << '/' << repository.name << ' '
                  << repository.stars << ' ' << repository.forks << ' '
                  << repository.language << ' ' << repository.updated_at << '\n';
    }
    std::cout << "Selected repositories: " << repositories.size() << '\n';
    std::cout << "Exported to: " << output_path.string() << '\n';
}

void export_repositories(
    const std::vector<Repository>& repositories, const std::filesystem::path& path) {
    RepositoryStore store;
    store.save(repositories, path.string());
}
