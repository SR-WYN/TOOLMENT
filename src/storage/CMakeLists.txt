# 查找依赖包
find_package(SQLiteCpp REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

# 定义源文件
set(STORAGE_SOURCES
    ConfigManager.cpp
    ConfigDao.cpp
    SQLDao.cpp
    Logger.cpp
)

# 定义头文件
set(STORAGE_HEADERS
    ConfigManager.hpp
    ConfigDao.hpp
    SQLDao.hpp
    Logger.hpp
)

# 创建 storage 库
add_library(storage
    ${STORAGE_SOURCES}
    ${STORAGE_HEADERS}
)

# 配置头文件搜索路径
target_include_directories(storage PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 链接依赖库
target_link_libraries(storage
    PUBLIC
        const
        utils
        SQLiteCpp
        nlohmann_json::nlohmann_json
    PRIVATE
        Qt6::Core
)