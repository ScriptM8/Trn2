cmake_minimum_required(VERSION 3.17)
project(Trn2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Trn2 main.cpp Transaction.cpp Transaction.h log.h tinyxml/tinyxml.cpp tinyxml/tinystr.h tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinystr.cpp)