cmake_minimum_required(VERSION 3.10)
project(BankManagementSystem)
include_directories(Core Models Screens UI)

file(GLOB_RECURSE SOURCES
    "Main.cpp"
    "Core/*.h"
    "Models/*.h"
    "Screens/**/*.h"
    "UI/*.h"
)

add_executable(app ${SOURCES})