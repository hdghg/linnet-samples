add_library(common args.h args.c socket/common.h socket/common.c)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})