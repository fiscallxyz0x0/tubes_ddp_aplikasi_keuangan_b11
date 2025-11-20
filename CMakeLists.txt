cmake_minimum_required(VERSION 3.10)

# Nama project
project(KeuanganApp C)

# Tentukan standar C
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Tambahkan folder include agar header dikenali
include_directories(${PROJECT_SOURCE_DIR}/include)

# Ambil semua file .c dari src (rekursif ke subfolder)
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Buat executable dari semua file sumber
add_executable(keuangan_mahasiswa ${SRC_FILES})
