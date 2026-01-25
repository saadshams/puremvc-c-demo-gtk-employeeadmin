cmake_minimum_required(VERSION 4.0)
project(employeeadmin C)

set(CMAKE_C_STANDARD 11)

# 2️⃣ Find dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4>=4.14)
#find_package(puremvc REQUIRED CONFIG)

add_executable(employeeadmin main.c
        application.c
        model/enum/dept_enum.c
        model/enum/role_enum.c
        model/vo/user_vo.c
        model/vo/role_vo.c
        view/components/user_list.c
        view/components/user_form.c
        view/components/user_role.c
        view/components/user_role.h)

target_link_libraries(employeeadmin PRIVATE PkgConfig::GTK4)
#target_link_libraries(employeeadmin PUBLIC puremvc::puremvc)

