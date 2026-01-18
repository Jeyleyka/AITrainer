cmake_minimum_required(VERSION 3.16)
project(ai_backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon REQUIRED)

add_executable(ai_backend
    main.cpp
)

target_link_libraries(ai_backend
    Drogon::Drogon
)