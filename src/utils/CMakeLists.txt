# 定义源文件
set(UTILS_SOURCES
)

# 定义头文件
set(UTILS_HEADERS
    Singleton.hpp
)

# 创建 utils 库
add_library(utils
    ${UTILS_SOURCES}
    ${UTILS_HEADERS}
)

# 配置头文件搜索路径
target_include_directories(utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)