# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\analizador_lexico_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\analizador_lexico_autogen.dir\\ParseCache.txt"
  "analizador_lexico_autogen"
  )
endif()
