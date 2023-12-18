FROM debian:bullseye

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    git \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install meson==1.0.0 ninja==1.11.1
WORKDIR /app
COPY . /app

RUN meson setup builddir && meson compile -C builddir

CMD ["./builddir/code/app"]
