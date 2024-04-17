cmake_minimum_required(VERSION 3.16)

project(Squaredle-Solver VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appSquaredle-Solver
    main.cpp
    ../../Backend/Algorithm.cpp ../../Backend/Algorithm.hpp
    ../../Backend/InputOutputProcessor.cpp ../../Backend/InputOutputProcessor.hpp
    ../../Backend/Trie.cpp ../../Backend/Trie.hpp
    ../../Backend/TrieNode.hpp
    ../../Backend/Parameters.hpp
)

qt_add_qml_module(appSquaredle-Solver
    URI Squaredle-Solver
    VERSION 1.0
    QML_FILES
        Main.qml
        RESOURCES Resources.qrc
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
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appSquaredle-Solver
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
