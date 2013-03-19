cmake_minimum_required(VERSION 2.6)

project(tatowiki)

# set the version
set(PROJECT_VERSION "0.5.6")
set(ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-${PROJECT_VERSION})
add_custom_target(
    dist
    COMMAND git archive --prefix=${ARCHIVE_NAME}/ HEAD
        | bzip2 > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.bz2
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)


enable_testing()


#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(
    src
)


set(
    FRAMEWORK_BUILD_DIR
    build
)


file(
    GLOB
    controllers_files
    src/controllers/*
    src/controllers/webs/*
    src/controllers/generics/*
)

file(
    GLOB
    models_files
    src/models/*
)

file(
    GLOB
    results_files
    src/results/*
)

file(
    GLOB
    contents_files
    src/contents/*
)


file(
    GLOB
    generics_files
    src/generics/*
)


add_executable(
    tatowiki
    src/TatoWiki.cpp
    src/main.cpp
    ${controllers_files}
    ${models_files}
    ${generics_files}
    ${results_files}
    ${contents_files}
    view_web.cpp
)

set(
    TATOWIKI_LIBS
    cppcms
    cppdb
    booster
    sqlite3
    cppcmsskel
    markdown
)


target_link_libraries(
    tatowiki
    ${TATOWIKI_LIBS}
)


add_custom_command(
    OUTPUT view_web.cpp
    COMMAND cppcms_tmpl_cc 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/webs/layouts/master.tmpl
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/webs/*/*.tmpl 
        -o view_web.cpp
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/webs/*/*.tmpl 
)


# unit test for the models
set(
    ARTICLES_MODEL_TESTS
    articles
    get_from_lang_and_slug
    create_from_lang_and_slug
    add_to_group
)

foreach(TEST ${ARTICLES_MODEL_TESTS})


    add_executable(
        tests/models/articles/${TEST}
        tests/models/articles/${TEST}.cpp
        src/models/Articles.cpp 
        tests/models/articles
    )
    target_link_libraries(tests/models/articles/${TEST} ${TATOWIKI_LIBS})

    add_custom_command(
        OUTPUT tests/models/articles
        COMMAND mkdir -p tests/models/articles
    ) 


    add_test(
        models/articles/${TEST}
        tests/models/articles/${TEST}
    )


        
endforeach()


