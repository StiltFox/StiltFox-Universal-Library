add_library(sqlite3 sqlite3.c)
add_library(shell shell.c)
target_link_libraries(shell sqlite3)