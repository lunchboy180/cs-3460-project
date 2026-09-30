cmake_minimum_required(VERSION 3.20)

project(Slitherer
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(httplib CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(Slitherer
    src/main.cpp
    src/github_client.cpp
    src/repository_parser.cpp
    src/repository_store.cpp
)

target_link_libraries(Slitherer PRIVATE
    httplib::httplib
    nlohmann_json::nlohmann_json
)
