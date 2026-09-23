cmake_minimum_required(VERSION 3.20)

project(Slitherer LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
	httplib
	GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
	GIT_TAG v0.18.3
	GIT_SHALLOW TRUE
)
FetchContent_Declare(
	nlohmann_json
	GIT_REPOSITORY https://github.com/nlohmann/json.git
	GIT_TAG v3.11.3
	GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(httplib nlohmann_json)
find_package(OpenSSL REQUIRED)

add_executable(Slitherer
	src/main.cpp
	src/github_client.cpp
	src/repository_parser.cpp
	src/repository_store.cpp
)

target_compile_features(Slitherer PRIVATE cxx_std_20)
set_target_properties(Slitherer PROPERTIES CXX_STANDARD_REQUIRED ON)

target_link_libraries(Slitherer PRIVATE
	httplib::httplib
	nlohmann_json::nlohmann_json
	OpenSSL::SSL
	OpenSSL::Crypto
)