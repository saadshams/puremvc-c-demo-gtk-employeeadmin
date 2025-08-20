cmake_minimum_required(VERSION 4.0)
project(employeeadmin C)

set(CMAKE_C_STANDARD 11)

# 2️⃣ Find dependencies
find_package(puremvc REQUIRED CONFIG)

add_executable(employeeadmin main.c)

# 4️⃣ Target properties
target_include_directories(employeeadmin
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)
target_link_libraries(puremvc-c-demo-gtk-employeeadmin PUBLIC puremvc::puremvc)

# 5️⃣ Install rules
include(GNUInstallDirs)

install(TARGETS employeeadmin
        EXPORT employeeadmin-config
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT EmployeeAdminRunTime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT EmployeeAdminRunTime NAMELINK_COMPONENT EmployeeAdminDevelopment
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT EmployeeAdminDevelopment)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
