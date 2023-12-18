# Use an official Debian image as the base image
FROM debian:bullseye

# Set non-interactive mode for apt-get
ARG DEBIAN_FRONTEND=noninteractive

# Install necessary packages in a single RUN step to reduce layer count
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    git \
    && rm -rf /var/lib/apt/lists/*

# Upgrade pip to the latest version
RUN pip3 install --no-cache-dir --upgrade pip

# Install specific versions of Meson and Ninja
RUN pip3 install --no-cache-dir meson==1.0.0 ninja==1.11.1

# Set the working directory
WORKDIR /app

# Copy the entire project into the container
COPY . /app

# Set up the build directory and compile the project
RUN meson setup builddir && \
    meson compile -C builddir

# Specify the default command to run when the container starts
CMD ["./builddir/code/app"]
