cmake_minimum_required(VERSION 3.22)
project(ClientSide)

set(CMAKE_CXX_STANDARD 14)

add_executable(ClientSide main.cpp MessageDErreur.h TelechargementDuFichier.h SequenceDIdentification.h checkforerror.h SelectionDuFichier.h)
