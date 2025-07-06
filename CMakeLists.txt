cmake_minimum_required(VERSION 3.30)

project(exe)


include(cmake/Logging.cmake)
include(cmake/Ccache.cmake)
include(cmake/Helpers.cmake)
include(cmake/CheckCompiler.cmake)
include(cmake/CompileOptions.cmake)
include(cmake/Sanitize.cmake)
include(cmake/Platform.cmake)
include(cmake/Development.cmake)

add_subdirectory(third_party)

# This must be included after library so that
# third party code is not affected
include(cmake/Werror.cmake)
include(cmake/Task.cmake)



begin_task()

#add_task_library(src_exe)

add_subdirectory(tests)

#add_task_playground(playground)


end_task()