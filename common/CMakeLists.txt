add_library(common args.h args.c socket/common.h socket/common.c io.c io.h)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})