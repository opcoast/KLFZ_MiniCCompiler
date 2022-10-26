cmake_minimum_required(VERSION 3.23)
PROJECT(KLFZ_Lex)
    set(SOURCES
        KLFZ_Lex.cpp
        )

    add_executable(${PROJECT_NAME} ${SOURCES})

    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
    target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)