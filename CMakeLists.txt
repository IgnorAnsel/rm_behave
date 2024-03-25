cmake_minimum_required(VERSION 3.8)
project(rm_behave)
set(CMAKE_CXX_STANDARD 17)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(behaviortree_cpp REQUIRED)  # 添加行为树库
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rm_decision_interfaces REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(rclcpp_action REQUIRED)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# 添加头文件路径
include_directories(include ${behaviortree_cpp_INCLUDE_DIRS})

set(PACKAGE_INCLUDE_DEPENDS 
  behaviortree_cpp
)

# 创建可执行文件
add_executable(rotate_action_node src/src/behaviortree_rotation.cpp)
add_executable(auto src/src/auto.cpp)
add_executable(sbauto src/src/sbauto.cpp src/src/sb.cpp src/src/actions.cpp src/src/is_actions.cpp)
# 链接依赖项
ament_target_dependencies(rotate_action_node rclcpp behaviortree_cpp geometry_msgs )
ament_target_dependencies(auto rclcpp behaviortree_cpp geometry_msgs sensor_msgs )
ament_target_dependencies(sbauto rclcpp behaviortree_cpp geometry_msgs sensor_msgs rm_decision_interfaces nav2_msgs rclcpp_action)

# 安装可执行文件
install(TARGETS
  auto
  rotate_action_node
  sbauto
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

