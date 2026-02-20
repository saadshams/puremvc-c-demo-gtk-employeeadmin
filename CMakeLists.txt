cmake_minimum_required(VERSION 3.5)
project(employeeadmin C)

set(CMAKE_C_STANDARD 11)

# 2️⃣ Find dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4>=4.14)

# 2. External Subprojects
add_subdirectory("../puremvc-c-multicore-framework2" puremvc)

# The Core Library
add_library(core
        src/application.c
        src/application_facade.c
        src/controller/startup_command.c
        src/model/user_proxy.c
        src/model/role_proxy.c
        src/model/enum/dept_enum.c
        src/model/enum/role_enum.c
        src/model/valueObject/user_vo.c
        src/model/valueObject/role_vo.c
        src/view/user_list_mediator.c
        src/view/user_form_mediator.c
        src/view/user_role_mediator.c
        src/view/components/user_list.c
        src/view/components/user_form.c
        src/view/components/user_role.c)

# Compiler Sanitizers & Warnings (cross-platform, strict)
target_compile_options(core PRIVATE
        $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Werror -fsanitize=address,undefined -fno-omit-frame-pointer>
        $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_link_options(core PUBLIC
        $<$<C_COMPILER_ID:GNU,Clang>:-fsanitize=address,undefined>)

target_link_libraries(core PUBLIC puremvc PkgConfig::GTK4)
target_include_directories(core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/src)

# The Executable
add_executable(employeeadmin src/main.c)
target_link_libraries(employeeadmin PRIVATE core)

option(EMPLOYEE_ADMIN_BUILD_TESTS "Build EmployeeAdmin Tests" ${PROJECT_IS_TOP_LEVEL})
if (EMPLOYEE_ADMIN_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()

message(STATUS "PROJECT_IS_TOP_LEVEL = ${PROJECT_IS_TOP_LEVEL}")
message(STATUS "EMPLOYEE_ADMIN_BUILD_TESTS = ${EMPLOYEE_ADMIN_BUILD_TESTS}")
