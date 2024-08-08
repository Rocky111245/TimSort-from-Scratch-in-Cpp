# Use the latest Ubuntu image
FROM ubuntu:latest

# Metadata
LABEL authors="rakib"

# Set the working directory
WORKDIR /app

# Install necessary packages
RUN apt-get update && \
    apt-get install -y cmake g++ git

# Copy the project files into the container
COPY . .

# Create a build directory and run CMake
RUN mkdir build && \
    cd build && \
    cmake .. && \
    cmake --build .

# Set the default command to run the main program
CMD ["./build/TimSortMain"]
