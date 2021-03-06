include (FindPackageHandleStandardArgs)

MESSAGE (STATUS $ENV{AWESOMIUM_ROOT})

find_path(AWESOMIUM_INCLUDE_DIR Awesomium
	PATH_SUFFIXES include
	PATHS
	${AWESOMIUM_ROOT}
	${AWESOMIUM_ROOT}/include
	$ENV{AWE_DIR}include
	$ENV{AWESOMIUM_ROOT}
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local/
	/usr/
	/sw          # Fink
	/opt/local/  # DarwinPorts
	/opt/csw/    # Blastwave
	/opt/)
	
find_library(AWESOMIUM_LIBRARY 
	NAMES awesomium.lib libawesomium-1-7.so.4.0
	PATH_SUFFIXES lib64 lib build/lib 
	PATHS
	${AWESOMIUM_ROOT}
	${AWESOMIUM_ROOT}/bin
	$ENV{AWE_DIR}build/lib
	$ENV{AWESOMIUM_ROOT}
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local/
	/usr/
	/sw          # Fink
	/opt/local/  # DarwinPorts
	/opt/csw/    # Blastwave
	/opt/)

find_package_handle_standard_args (Awesomium DEFAULT_MSG AWESOMIUM_INCLUDE_DIR AWESOMIUM_LIBRARY)
mark_as_advanced (AWESOMIUM_INCLUDE_DIR AWESOMIUM_LIBRARY)

if (AWESOMIUM_FOUND)
	message (STATUS "Found Awesomium: ${AWESOMIUM_INCLUDE_DIR}")
endif ()