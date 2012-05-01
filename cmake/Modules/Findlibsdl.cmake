include(LibFindMacros)

find_path(LIBSDL_INCLUDE_DIR NAMES sdl.h PATHS ${LIBSDL_PKGCONF_INCLUDE_DIRS})

find_library(LIBSDL_LIBRARY NAMES sdl PATHS ${LIBSDL_PKGCONF_LIBRARY_DIRS})

set(LIBSDL_PROCESS_INCLUDES LIBSDL_INCLUDE_DIR)
set(LIBSDL_PROCESS_LIBS LIBSDL_LIBRARY LIBSDL_LIBRARIES)

libfind_process(LIBSDL)