cmake_minimum_required(VERSION 2.8)

project(GalArch LANGUAGES C)

include_directories(include)

add_executable(GalArch
    sources/main.c
    sources/packer.c
    sources/headers.c
)
