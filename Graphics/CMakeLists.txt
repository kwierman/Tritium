#Get together the sources
file(GLOB module_sources *.cxx)
file(GLOB module_headers *.h)

#Make the library
add_library(TritiumGraphics SHARED ${module_sources} ${module_headers})
target_link_libraries(TritiumGraphics ProtiumThreads ProtiumSingleton)
set_target_properties(TritiumGraphics PROPERTIES LINKER_LANGUAGE CXX)
install(TARGETS TritiumGraphics DESTINATION lib EXPORT TritiumConfig)

#Install Headers
install(FILES ${module_headers} DESTINATION include/Tritium/Graphics)

