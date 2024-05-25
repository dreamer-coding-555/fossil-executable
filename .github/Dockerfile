# Choose base image based on the Linux distribution
ARG DISTRO
FROM ${DISTRO}

# Set non-interactive environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    clang \
    gobjc \
    gobjc++ \
    build-essential \
    python3 \
    python3-pip \
    rustc \
    cargo \
    gdc \
    && rm -rf /var/lib/apt/lists/*

# Install Ninja and Meson using pip
RUN python3 -m pip install --upgrade pip \
    && python3 -m pip install meson ninja

# Set the working directory
WORKDIR /app

# Copy the project files into the container
COPY . .

# Define default command to run when the container starts
CMD ["bash"]
