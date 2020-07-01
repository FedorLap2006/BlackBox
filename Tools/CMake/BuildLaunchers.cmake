set(LAUNCHER_DIR)
if (OPTION_ENGINE)
	if (NOT ANDROID)
		set(OPTION_LAUNCHER_EXECUTABLE "GameLauncher" CACHE STRING "Base file name for the game executable (without file extension)")
	endif()
	if (ANDROID)
		set(LAUNCHER_DIR "src/Launcher/AndroidLauncher")
	elseif (LINUX)
		set(LAUNCHER_DIR "src/Launcher/LinuxLauncher")
	elseif (WINDOWS)
		#set(LAUNCHER_DIR"src/Launcher/DedicatedLauncher")
		set(LAUNCHER_DIR "src/Launcher/WindowsLauncher")
	endif ()
endif()

add_subdirectory(${LAUNCHER_DIR})
set_solution_startup_target(Launcher)
set_property(TARGET Launcher PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
