
cmake_minimum_required(VERSION 3.14)
#定义工程的名字
PROJECT(TEST_CALCULATOR)

#引入QT的包
find_package(Qt5Widgets)


#定义工程包含的文件夹和文件
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#main
set(PROJECT_MAIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB project_main_source_files ${PROJECT_MAIN_DIR}/*.cpp)
source_group("Source Files" FILES ${project_main_source_files})
#algorithm
set(PROJECT_ALGORITHM_DIR "${PROJECT_MAIN_DIR}/algorithm")
file(GLOB project_algorithm_header_files ${PROJECT_ALGORITHM_DIR}/*.h)
file(GLOB project_algorithm_source_files ${PROJECT_ALGORITHM_DIR}/*.cpp)
source_group("Header Files\\algorithm" FILES ${project_algorithm_header_files})
source_group("Source Files\\algorithm" FILES ${project_algorithm_source_files})
#ui
set(PROJECT_UI_DIR "${PROJECT_MAIN_DIR}/ui")
file(GLOB project_ui_header_files ${PROJECT_UI_DIR}/*.h)
file(GLOB project_ui_source_files ${PROJECT_UI_DIR}/*.cpp)
source_group("Header Files\\ui" FILES ${project_ui_header_files})
source_group("Source Files\\ui" FILES ${project_ui_source_files})


#将上述文件夹include到工程里,就不用写路径了
include_directories(${PROJECT_MAIN_DIR} 
					${PROJECT_ALGORITHM_DIR}
					${PROJECT_UI_DIR}
					${Qt5Widgets_INCLUDE_DIRS})

#定义程序用了哪些文件
add_executable(${PROJECT_NAME}
	           ${project_main_source_files}
  	           ${project_algorithm_header_files}
	           ${project_algorithm_source_files}
			   ${project_ui_header_files}
			   ${project_ui_source_files})

 #连接QT的lib文件
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
#需要c++17的标准
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAG "/std:c++17")

#生成的程序放哪
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)