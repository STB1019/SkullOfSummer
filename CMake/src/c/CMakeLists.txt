#CMakeLists.txt beta
#Quando il compilatore effettuerà la compilazione, verrà aggiunta la flag "-I../include" (che dice dove stanno gli head file)
include_directories("../include")
#creo una variabile SOURCES e ci metto dentro tutti i file nella CWD (ossia src/c) che terminano con ".c"
file(GLOB SOURCES "*.c")
#faccio la stessa cosa con gli header
file(GLOB HEADERS "../include/*.h")

#ne devi attivare o una o l'altra! ${SOURCES} è la variabile creata poco fa
#questa funzione dice che il make deve creare una shared library (*.so)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
#se attiva questa funzione dice che il make deve creare un'eseguibile
#add_executable(${PROJECT_NAME} ${SOURCES})

#elenco delle librerie da linkare per poter completare la fase di linking correttamente
target_link_libraries(${PROJECT_NAME} "m")

#settiamo qualche informazione su come vogliamo creare il nostro oggetto (o la shared library o l'eseguibile)
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" #se è una libreria statica la dobbiamo creare in build/
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" #se è una libreria dinamica la dobbiamo creare in build/
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" # se è un esebuibile lo dobbiamo creare in build/
)

#usato per poter fare "sudo make install" quando stiamo costruendo una libreria dinamica
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${HEADERS} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")
#per poter usare immediatamente la libreria eseguiamo ldconfig
install(CODE "execute_process(COMMAND ldconfig)")
