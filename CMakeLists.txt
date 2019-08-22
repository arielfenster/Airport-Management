cmake_minimum_required(VERSION 3.8)
project(ex2)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp interface.h FilesManagment.cpp FilesManagment.h MyImplementation.cpp MyImplementation.h IDGenerator.cpp IDGenerator.h MyCustomer.cpp MyCustomer.h MyEmployee.cpp MyEmployee.h MyReservation.cpp MyReservation.h Date.cpp MyFlight.cpp MyFlight.h MyPlane.cpp MyPlane.h)
add_executable(ex2 ${SOURCE_FILES} interface.h FilesManagment.cpp FilesManagment.h MyImplementation.cpp MyImplementation.h IDGenerator.cpp IDGenerator.h MyCustomer.cpp MyCustomer.h MyEmployee.cpp MyEmployee.h MyReservation.cpp MyReservation.h Date.cpp MyFlight.cpp MyFlight.h MyPlane.cpp MyPlane.h)