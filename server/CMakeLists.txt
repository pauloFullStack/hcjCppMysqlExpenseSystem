cmake_minimum_required(VERSION 3.5)
project(crudCpp)

# Use file(GLOB_RECURSE ...) para encontrar todos os arquivos .cpp na pasta "src" e subdiretórios
file(GLOB_RECURSE ROUTE "route/*.cpp")
file(GLOB_RECURSE MODELS "models/*.cpp")
file(GLOB_RECURSE HELPER "helper/*.cpp")
file(GLOB_RECURSE CONTROLLERS "controllers/*.cpp")
file(GLOB_RECURSE ROOT "./*.cpp")

# Filtrar a lista de arquivos de origem para excluir CMakeCXXCompilerId.cpp
list(FILTER ROUTE EXCLUDE REGEX ".*CMakeCXXCompilerId.cpp$")
list(FILTER MODELS EXCLUDE REGEX ".*CMakeCXXCompilerId.cpp$")
list(FILTER HELPER EXCLUDE REGEX ".*CMakeCXXCompilerId.cpp$")
list(FILTER CONTROLLERS EXCLUDE REGEX ".*CMakeCXXCompilerId.cpp$")
list(FILTER ROOT EXCLUDE REGEX ".*CMakeCXXCompilerId.cpp$")

# Adicione todos os arquivos .cpp à compilação
add_executable(crudCpp ${ROUTE} ${MODELS} ${HELPER} ${CONTROLLERS} ${ROOT})

# Especifique as bibliotecas a serem vinculadas ao seu executável
target_link_libraries(crudCpp PRIVATE mysqlcppconn pthread)