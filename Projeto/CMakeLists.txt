cmake_minimum_required(VERSION 3.5)

project(ProjetoASC LANGUAGES C)

add_executable(ProjetoASC main.c)

include(GNUInstallDirs)
install(TARGETS ProjetoASC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
