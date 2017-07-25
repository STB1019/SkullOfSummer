#CMakeLists.txt alpha
cmake_minimum_required(VERSION 3.5.1) #versione di cmake minima
#quando esegui 'cmake ..' questo messaggio sarà stampato a video
message(INFO "You should call cmake when you are in build or in build. You hould call 'cmake ..'")
set(PROJECT_NAME "awesome-lib")
project(${PROJECT_NAME} VERSION 1.0)

#se non ho espresso un metodo di build, lo imposto come Debug: in questo modo verrà automaticamente aggiunta la
#flag "-g" di compilazione
if(NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

add_definitions(-Wfatal-errors) #per aggiungere delle flag di compilazione

# aggiunta del comando per disinstallare
add_custom_target(uninstall
    COMMAND xargs rm < install_manifest.txt
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}" 
    DEPENDS "${CMAKE_BINARY_DIR}/install_manifest.txt"
    COMMENT "Removes everything installed by sudo make install"
    VERBATIM
)

add_subdirectory(src/c) #per creare il Makefile serve andare a vedere il file CMakeLists.txt contenuto nella cartella src/c
