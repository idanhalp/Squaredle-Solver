cmake_minimum_required(VERSION 3.16)

project(Squaredle-Solver VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

set(CMAKE_AUTORCC ON)

set(BACKEND_FILES
    ${CMAKE_SOURCE_DIR}/Source/Backend/Algorithm.cpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/Algorithm.hpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/InputOutputProcessor.cpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/InputOutputProcessor.hpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/Trie.cpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/Trie.hpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/TrieNode.hpp
)

set(FRONTEND_FILES
    ${CMAKE_SOURCE_DIR}/Source/Frontend/gridmodel.h
    ${CMAKE_SOURCE_DIR}/Source/Frontend/gridmodel.cpp
    ${CMAKE_SOURCE_DIR}/Source/Frontend/main.cpp
    ${CMAKE_SOURCE_DIR}/Source/Frontend/resultsmodel.h
    ${CMAKE_SOURCE_DIR}/Source/Frontend/resultsmodel.cpp
    ${CMAKE_SOURCE_DIR}/Source/Frontend/Resources.qrc
)

set(SOURCES
    ${BACKEND_FILES}
    ${FRONTEND_FILES}
    ${CMAKE_SOURCE_DIR}/Source/Parameters.hpp
)

qt_add_executable(appSquaredle-Solver
    ${SOURCES}
)

qt_add_qml_module(appSquaredle-Solver
    URI SquaredleSolver
    VERSION 1.0
    QML_FILES
	Source/Frontend/Main.qml
	SOURCES
	${CMAKE_SOURCE_DIR}/Source/Frontend/mainmodule.h
	${CMAKE_SOURCE_DIR}/Source/Frontend/mainmodule.cpp
)

target_include_directories(appSquaredle-Solver PRIVATE
    ${CMAKE_SOURCE_DIR}/Source/Frontend
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSquaredle-Solver PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSquaredle-Solver
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSquaredle-Solver
    PRIVATE Qt6::Quick Qt6::qquicklayoutsplugin
)

include(GNUInstallDirs)
install(TARGETS appSquaredle-Solver
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
