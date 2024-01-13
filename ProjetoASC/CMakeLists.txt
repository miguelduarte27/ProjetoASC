cmake_minimum_required(VERSION 3.5)

project(ProjetoASC_IDEQt LANGUAGES C)

add_executable(ProjetoASC_IDEQt main.c)

include(GNUInstallDirs)
install(TARGETS ProjetoASC_IDEQt
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
