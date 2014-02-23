cmake_minimum_required(VERSION 2.6)

project(tatowiki)

# set the version
set(PROJECT_VERSION "0.23.0")
set(ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-${PROJECT_VERSION})
add_custom_target(
    dist
    COMMAND git archive --prefix=${ARCHIVE_NAME}/ HEAD
        | bzip2 > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.bz2
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)




set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-padded -Wno-global-constructors -Wno-weak-vtables -std=c++0x")

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
    view_tatoeba_skin_web.cpp
    view_ajax.cpp
    view_responsive_skin_web.cpp
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

###########################
# Part common to all skins
###########################
set(
    WEB_SKINS_COMMONS_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/src/views/webs/commons/
)

set(
    WEB_SKINS_COMMONS
    ${WEB_SKINS_COMMONS_DIR}/layouts/master.tmpl
    ${WEB_SKINS_COMMONS_DIR}/layouts/article_edition.tmpl
    ${WEB_SKINS_COMMONS_DIR}/*/*.tmpl
)



########################
#  Tatoeba skin
########################

set(
    TATOEBA_WEB_SKIN_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/src/views/webs/tatoeba
)

add_custom_command(
    OUTPUT view_tatoeba_skin_web.cpp
    COMMAND cppcms_tmpl_cc
        ${WEB_SKINS_COMMONS_DIR}/layouts/master.tmpl
        ${TATOEBA_WEB_SKIN_DIR}/layouts/master.tmpl
        ${WEB_SKINS_COMMONS_DIR}/layouts/article_edition.tmpl
        ${TATOEBA_WEB_SKIN_DIR}/layouts/article_edition.tmpl
        ${WEB_SKINS_COMMONS_DIR}/*/*.tmpl
        ${TATOEBA_WEB_SKIN_DIR}/*/*.tmpl
        -o view_tatoeba_skin_web.cpp
        -s tatoeba
    DEPENDS
        ${WEB_SKINS_COMMONS}
        ${TATOEBA_WEB_SKIN_DIR}/*/*.tmpl
)

########################
#  Default responsive skin
########################
set(
    RESPONSIVE_WEB_SKIN_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/src/views/webs/responsive
)

add_custom_command(
    OUTPUT view_responsive_skin_web.cpp
    COMMAND cppcms_tmpl_cc
        ${WEB_SKINS_COMMONS_DIR}/layouts/master.tmpl
        ${RESPONSIVE_WEB_SKIN_DIR}/layouts/master.tmpl
        ${WEB_SKINS_COMMONS_DIR}/layouts/article_edition.tmpl
        ${RESPONSIVE_WEB_SKIN_DIR}/layouts/article_edition.tmpl
        ${WEB_SKINS_COMMONS_DIR}/*/*.tmpl
        ${RESPONSIVE_WEB_SKIN_DIR}/*/*.tmpl
        -o view_responsive_skin_web.cpp
        -s responsive
    DEPENDS
        ${WEB_SKINS_COMMONS}
        ${RESPONSIVE_WEB_SKIN_DIR}/*/*.tmpl
)

########################
#  Ajax skin
########################
set(
    TATOEBA_AJAX_SKIN_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/src/views/ajax/
)

add_custom_command(
    OUTPUT view_ajax.cpp
    COMMAND cppcms_tmpl_cc
        ${TATOEBA_AJAX_SKIN_DIR}/layouts/json.tmpl
        ${TATOEBA_AJAX_SKIN_DIR}/*/*.tmpl
        -o view_ajax.cpp
        -s ajax
    DEPENDS
        ${TATOEBA_AJAX_SKIN_DIR}/*/*.tmpl
)



###############
# unit tests
###############


enable_testing()
    ######
    # Unit test for Models
    #####


    ######
    # Note: there's a little hack here
    # we define the classes   Class1 / Class2
    # and after we define "lists" of methods named Class1_models_methods
    # Class2_models_methods etc.  this way after we can do
    # foreach METHOD ${${CLASS_NAME}_methods}
    # to go through all methods of all class without duplicating cmake code
    #####



    set(
        MODULES
        models
    )


    ######
    # Note: there's a little hack here
    # we define the classes   Class1 / Class2
    # and after we define "lists" of methods named Class1_models_methods
    # Class2_models_methods etc.  this way after we can do
    # foreach METHOD ${${CLASS_NAME}_methods}
    # to go through all methods of all class without duplicating cmake code
    #####
    set(
        CLASSES_models
        Articles
    )



    # unit test for the models
    set(
        Articles_models_METHODS
        articles
        get_from_lang_and_slug
        create_from_lang_and_slug
        add_to_group
        get_group_id_from_lang_and_slug
        get_from_id
        edit_from_lang_and_slug
    )

    foreach(MODULE ${MODULES})
        message(
            STATUS
            "in module ${MODULE}"
        )
        foreach(CLASS ${CLASSES_${MODULE}})
            message(
                STATUS
                "in class ${CLASS}"
            )
            foreach(METHOD ${${CLASS}_${MODULE}_METHODS})
                #we are supposed to have a folder named with the
                #method named, and with inside one test by .cpp
                #file
                file(
                    GLOB
                    TESTS
                    tests/${MODULE}/${CLASS}/${METHOD}/*.cpp
                )

                #for each of these tests
                foreach(TEST_FULL_PATH ${TESTS})
                    #we do that in two time in order to extract only the test
                    #name out of the full path
                    string(
                        REGEX MATCH
                        "([^/]+)[.]cpp"
                        TEST
                        ${TEST_FULL_PATH}
                    )
                    string(
                        REGEX MATCH
                        "[^.]+"
                        TEST
                        ${TEST}
                    )

                    #just here to factorize
                    set(
                        EXECUTABLE_PATH
                        tests/${MODULE}/${CLASS}/${METHOD}
                    )

                    add_executable(
                        ${EXECUTABLE_PATH}/${TEST}
                        ${EXECUTABLE_PATH}/${TEST}.cpp
                        src/${MODULE}/${CLASS}.cpp
                        ${EXECUTABLE_PATH} #required to put it like this in order to
                                           #the custom command to know the test folder
                                           #has to be created (i.e without this the
                                           #custom command to create the directory will not
                                           #be triggered
                    )
                    target_link_libraries(${EXECUTABLE_PATH}/${TEST} ${TATOWIKI_LIBS})

                    #this command is to create the directory in the build directory
                    #in order to have the executable in the same hierarchy as their
                    #corresponding .cpp, in order to find them easily without the possiblity
                    #to have conflict between test name
                    add_custom_command(
                        OUTPUT  ${EXECUTABLE_PATH}
                        COMMAND mkdir -p ${EXECUTABLE_PATH}
                    )
                    add_test(
                        ${EXECUTABLE_PATH}/${TEST}
                        ${EXECUTABLE_PATH}/${TEST}
                    )

                endforeach()
            endforeach()
        endforeach()
    endforeach()


