FROM mcr.microsoft.com/devcontainers/cpp:0-ubuntu-22.04

# Install dependencies
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y \
        libcurl4-openssl-dev \
        nlohmann-json3-dev

# Set the default working directory
WORKDIR /workspace