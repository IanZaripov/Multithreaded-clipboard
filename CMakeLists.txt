cmake_minimum_required(VERSION 3.10)
project(Infotecs)

set(CMAKE_CXX_STANDARD 17)


add_executable(Infotecs
    main.cpp
    thread_reader.cpp
    thread_writer.cpp
    Buffer.cpp
)