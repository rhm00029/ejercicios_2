cmake_minimum_required(VERSION 4.1)
project(ejercicios_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(MaquinaExpendedora src/main.c
        src/funciones.c
)
target_include_directories(MaquinaExpendedora PUBLIC include)