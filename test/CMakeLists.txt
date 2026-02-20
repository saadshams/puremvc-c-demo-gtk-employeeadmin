add_executable(UserProxyTest model/user_proxy_test.c)
target_link_libraries(UserProxyTest PRIVATE core)
add_test(NAME EmployeeAdmin.UserProxyTest COMMAND UserProxyTest)
