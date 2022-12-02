# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(GoogleTest)

add_executable(FileOpsTest FileOps.cpp)
target_link_libraries(FileOpsTest GTest::gtest_main FileOps)
gtest_discover_tests(FileOpsTest)

add_executable(SqliteConnectionTest SqliteConnection.cpp)
target_link_libraries(SqliteConnectionTest GTest::gtest_main SqliteConnection sqlite3 FileOps)
gtest_discover_tests(SqliteConnectionTest)