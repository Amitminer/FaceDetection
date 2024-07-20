cmake_minimum_required(VERSION 3.12)
project(FaceDetection VERSION 1.0.0)

# Set the C++ standard to C++17 and mark it as required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the OpenCV package and ensure it is found
find_package(OpenCV REQUIRED)

# Include the directories for OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Define the executable target
add_executable(${PROJECT_NAME}
    src/main.cpp        # Source file for the main application
    src/frontalface.h   # Header file for the Haar Cascade data
)

# Link the executable with the OpenCV libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

# Set the output directory for the compiled executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

