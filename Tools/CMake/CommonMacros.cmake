macro(add_headers)
	file(GLOB_RECURSE INCLUDE_FILES ${BLACKBOX_INCLUDE_DIRS}/${PROJECT_NAME}/*.hpp ${BLACKBOX_INCLUDE_DIRS}/${PROJECT_NAME}/*.h)
	target_sources(${PROJECT_NAME}
		PRIVATE
		${INCLUDE_FILES}
	)
	source_group(
		TREE ${BLACKBOX_INCLUDE_DIRS}/${PROJECT_NAME}
		PREFIX "Header Files"
		FILES
		${INCLUDE_FILES}
	)
endmacro()