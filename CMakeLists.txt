cmake_minimum_required(VERSION 3.17)
project(Flac_decode_cpp)

set(CMAKE_CXX_STANDARD 11)

add_executable(Flac_decode_cpp main.cpp bit_stream_helper.cpp bit_stream_helper.hpp flac_decode.cpp flac_decode.hpp)