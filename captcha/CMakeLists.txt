cmake_minimum_required(VERSION 3.16)
project(captcha)

set(CMAKE_CXX_STANDARD 14)

add_executable(captcha main.c libcaptcha.c)