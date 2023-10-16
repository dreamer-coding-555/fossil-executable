# Use an official base image suitable for your application and compatible with your target systems.
# For example, for a Debian-based system, you can use "debian:bullseye" as the base image.
FROM debian:bullseye

# Update the package list and install any necessary dependencies.
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install meson==1.0.0 ninja==1.11.1

# Create a directory for your application.
WORKDIR /app
COPY . /app

RUN meson setup builddir && meson compile -C builddir

CMD ["./builddir/code/app"]
