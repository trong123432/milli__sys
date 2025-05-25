cmake_minimum_required(VERSION 3.10)
project(MilitarySystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Thêm các cờ tối ưu hóa cho Debug/Release
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(-O0 -g)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(-O2)
endif()

# Thêm các file nguồn
add_executable(MilitarySystem
        src/BinhSi.cpp
        src/main.cpp
        src/QuanLiQuanDoi.cpp
        src/QuanNhan.cpp
        src/SiQuan.cpp
        src/WindowHandler.cpp
)

# Định nghĩa biên dịch
target_compile_definitions(MilitarySystem PRIVATE UNICODE _UNICODE WIN32)

# Liên kết thư viện WinAPI
target_link_libraries(MilitarySystem PRIVATE kernel32 user32 gdi32 comdlg32 advapi32 comctl32)

# Đảm bảo CMake tìm thấy các file header
target_include_directories(MilitarySystem PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_options(MilitarySystem PRIVATE -mwindows)

# Tạo thư mục data trong thư mục build và sao chép file dữ liệu
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data)
file(COPY ${CMAKE_SOURCE_DIR}/data/solider_list.txt
        DESTINATION ${CMAKE_BINARY_DIR}/data)