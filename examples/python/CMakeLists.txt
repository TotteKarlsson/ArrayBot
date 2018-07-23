CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(PythonExamples)

FILE (GLOB examples *.py)

if(INSTALL_PYTHON_EXAMPLES)
    install (   
        FILES ${examples}			 	
        DESTINATION examples 
        COMPONENT python_examples
    )
endif()



