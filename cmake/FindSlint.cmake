set(SLINT_ROOT ${CMAKE_SOURCE_DIR}/install)
find_path (SLINT_INCLUDE_DIR 
	NAMES slint.h 
	PATHS ${SLINT_ROOT}/include
	PATH_SUFFIXES slint
  )

find_library (SLINT_LIBRARY
	Names libslint_cpp.dylib
	PATHS ${SLINT_ROOT}/lib)

include(${SLINT_ROOT}/lib/cmake/Slint/SlintConfig.cmake)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Slint DEFAULT_MSG
    SLINT_LIBRARY SLINT_INCLUDE_DIR
)

# if(Slint_FOUND)
#     add_library(Slint::Slint UNKNOWN IMPORTED)
#     set_target_properties(Slint::Slint PROPERTIES
#         IMPORTED_LOCATION ${SLINT_LIBRARY}
#         INTERFACE_INCLUDE_DIRECTORIES ${SLINT_INCLUDE_DIR}
#     )
# endif()
