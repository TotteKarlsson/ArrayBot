SET(target atCore)

INCLUDE_DIRECTORIES(
.
${ATAPI_ROOT}
${ATAPI_ROOT}/source
${CG_BOOST_ROOT}
${TR1_ROOT}
${THIRD_PARTY_INSTALL_PREFIX}/include
${THIRD_PARTY_INSTALL_PREFIX}/include/dsl
)

SET(src
atATObject
atCore
atExceptions
)

link_directories(
${THIRD_PARTY_INSTALL_PREFIX}/lib
)


#===== Shared library
if(${BUILD_SHARED_LIBS})
    ADD_LIBRARY(${target} SHARED
    ${src}
    )

    SET_PROPERTY(TARGET ${target}  PROPERTY COMPILE_DEFINITIONS 
    AT_EXPORT_CORE
    )

    TARGET_LINK_LIBRARIES(${target} 
        ${THIRD_PARTY_INSTALL_PREFIX}/lib/dslFoundation.lib
    )


    INSTALL(    
    TARGETS ${target} 
    RUNTIME DESTINATION bin COMPONENT core
    LIBRARY DESTINATION lib COMPONENT core
    ARCHIVE DESTINATION lib COMPONENT core
    )            
endif()

#===== General Installs
if(${INSTALL_CXX_LIBS})
FILE (GLOB headers *.h)
INSTALL (   FILES ${headers}			 	
            DESTINATION include/atexplorer 
            COMPONENT cxx_headers)

endif()

