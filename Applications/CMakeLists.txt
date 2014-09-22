#file(GLOB applications *.cxx)
file(GLOB applications tritium_*.cxx)

foreach(_app ${applications})
	get_filename_component (name_without_extension ${_app} NAME_WE)
	add_executable(${name_without_extension} ${_app} )
	target_link_libraries(${name_without_extension} TritiumGraphics ProtiumSingleton ProtiumThreads)
	install(TARGETS ${name_without_extension} DESTINATION bin EXPORT TritiumConfig)
endforeach()