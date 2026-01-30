cmake_minimum_required(VERSION 3.16)
project(ai_backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon REQUIRED)
find_package(CURL REQUIRED)

add_executable(ai_backend
    main.cpp
    controllers/HealthController.cc
    controllers/InferController.cc
    services/AiService.cc
)

target_link_libraries(ai_backend
    Drogon::Drogon
    CURL::libcurl
)