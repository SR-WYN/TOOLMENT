cmake_minimum_required(VERSION 3.19)
project(TOOLMENT LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找依赖包
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(nlohmann_json 3.2.0 REQUIRED)

# Qt 标准设置与自动化
qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 引入子模块
add_subdirectory(src/const)
add_subdirectory(src/utils)
add_subdirectory(src/storage)

# 定义源文件
set(TOOLMENT_SOURCES
    main.cpp
    mainwindow.cpp
)

# 定义头文件
set(TOOLMENT_HEADERS
    mainwindow.h
)

# 定义 UI 文件
set(TOOLMENT_UI
    mainwindow.ui
)

# 生成主程序
qt_add_executable(TOOLMENT
    ${TOOLMENT_SOURCES}
    ${TOOLMENT_HEADERS}
    ${TOOLMENT_UI}
)

# 配置头文件搜索路径
target_include_directories(TOOLMENT PRIVATE
    ${MYSQLPP_INCLUDE_DIRS}
)

# 链接依赖库
target_link_libraries(TOOLMENT PRIVATE
    const
    utils
    storage
    Qt6::Core
    Qt6::Widgets
)

# 构建后操作：复制配置文件并创建运行所需目录
add_custom_command(TARGET TOOLMENT POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.json
        $<TARGET_FILE_DIR:TOOLMENT>/config.json
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:TOOLMENT>/logs
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:TOOLMENT>/db
    COMMENT "Copying config.json and creating runtime directories"
)

# ----------------- 安装与部署配置 -----------------
include(GNUInstallDirs)

install(TARGETS TOOLMENT
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# 自动生成 Qt 部署脚本 (Windows/macOS)
if(WIN32 OR APPLE)
    qt_generate_deploy_app_script(
        TARGET TOOLMENT
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT ${deploy_script})
endif()

# 配置文件安装路径
if(WIN32)
    install(FILES config.json DESTINATION .)
elseif(APPLE)
    install(FILES config.json DESTINATION TOOLMENT.app/Contents/MacOS)
else()
    install(FILES config.json DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()