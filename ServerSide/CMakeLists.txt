cmake_minimum_required(VERSION 3.22)
project(ServerSide)

set(CMAKE_CXX_STANDARD 14)

add_executable(ServerSide main.cpp MessageDErreur.h SequenceDIdentification.h SelectionDuFichier.h)
