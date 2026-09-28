#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

struct Repository {
    std::string owner;
    std::string name;
    std::string description;
    std::uint64_t stars{};
    std::uint64_t forks{};
    std::string language;
    std::uint64_t size{};
    std::string updated_at;
    std::string url;
};

struct SearchOptions {
    std::string query;
    std::size_t count{100};
};