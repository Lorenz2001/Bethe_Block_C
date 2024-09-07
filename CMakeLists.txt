cmake_minimum_required(VERSION 3.10)
project(Bethe_Block)


# Trova la configurazione ROOT
find_package(ROOT REQUIRED)

# Aggiungi le directory delle intestazioni ROOT
include_directories(${ROOT_INCLUDE_DIRS})

# Aggiungi le librerie di ROOT
link_directories(${ROOT_LIBRARY_DIRS})

# Aggiungi le opzioni del compilatore per ROOT
add_definitions(${ROOT_CXX_FLAGS})


add_executable(Bethe_Block main.cpp)



# Linka le librerie ROOT con il tuo eseguibile
target_link_libraries(myprogram ${ROOT_LIBRARIES})
