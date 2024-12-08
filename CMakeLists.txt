cmake_minimum_required(VERSION 3.16)

project(Squaredle-Solver VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

set(WARNING_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${WARNING_FLAGS} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${WARNING_FLAGS} -O3")

set(CMAKE_AUTORCC ON)

set(BACKEND_FILES
    ${CMAKE_SOURCE_DIR}/Source/Backend/Algorithm/Algorithm.cpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/Algorithm/Algorithm.hpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/Trie/Trie.cpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/Trie/Trie.hpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/Trie/TrieNode.cpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/Trie/TrieNode.hpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/WordProcessing/WordProcessing.cpp
    ${CMAKE_SOURCE_DIR}/Source/Backend/WordProcessing/WordProcessing.hpp
)

set(FRONTEND_FILES
    ${CMAKE_SOURCE_DIR}/Source/Frontend/GridModel/gridmodel.h
    ${CMAKE_SOURCE_DIR}/Source/Frontend/GridModel/gridmodel.cpp
    ${CMAKE_SOURCE_DIR}/Source/Frontend/main.cpp
    ${CMAKE_SOURCE_DIR}/Source/Frontend/ResultsModel/resultsmodel.h
    ${CMAKE_SOURCE_DIR}/Source/Frontend/ResultsModel/resultsmodel.cpp
    ${CMAKE_SOURCE_DIR}/Source/Frontend/Resources.qrc
)

set(TEST_FILES
    ${CMAKE_SOURCE_DIR}/Tests/Algorithm/Algorithm.cpp
    ${CMAKE_SOURCE_DIR}/Tests/Algorithm/Algorithm.hpp
    ${CMAKE_SOURCE_DIR}/Tests/Main.cpp
    ${CMAKE_SOURCE_DIR}/Tests/Trie/Trie.cpp
    ${CMAKE_SOURCE_DIR}/Tests/Trie/Trie.hpp
)

set(TEST_SOURCES
    ${BACKEND_FILES}
    ${TEST_FILES}
    ${CMAKE_SOURCE_DIR}/Source/Frontend/Resources.qrc
)

set(SOURCES
    ${BACKEND_FILES}
    ${FRONTEND_FILES}
    ${CMAKE_SOURCE_DIR}/Source/Parameters.hpp
)

set(QML_FILES
    Source/Frontend/Components/GameGrid.qml
    Source/Frontend/Components/HighlightTimer.qml
    Source/Frontend/Components/Popups/ErrorPopup.qml
    Source/Frontend/Components/Popups/GetPuzzlePopup.qml
    Source/Frontend/Components/Popups/Popups.qml
    Source/Frontend/Components/Results.qml
    Source/Frontend/Main.qml
)

qt_add_executable(appSquaredle-Solver
    ${SOURCES}
)

qt_add_executable(test
    ${TEST_SOURCES}
)

qt_add_qml_module(appSquaredle-Solver
    URI SquaredleSolver
    VERSION 1.0
    QML_FILES
        ${QML_FILES}
        Source/Frontend/GetPuzzle.js


    SOURCES
        ${CMAKE_SOURCE_DIR}/Source/Frontend/MainModule/mainmodule.h
        ${CMAKE_SOURCE_DIR}/Source/Frontend/MainModule/mainmodule.cpp

)

target_include_directories(appSquaredle-Solver PRIVATE
    ${CMAKE_SOURCE_DIR} # Addresses should be relative to the root.
    ${CMAKE_SOURCE_DIR}/Source/Frontend/MainModule
)

target_include_directories(test PRIVATE
    ${CMAKE_SOURCE_DIR} # Addresses should be relative to the root.
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

target_link_libraries(test
    PRIVATE Qt6::Test
)

include(GNUInstallDirs)
install(TARGETS appSquaredle-Solver
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
