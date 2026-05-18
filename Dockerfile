FROM ubuntu:22.04 AS builder
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /src
COPY . .
RUN cmake -S . -B build \
        -DCMAKE_BUILD_TYPE=Release \
        && cmake --build build --parallel "$(nproc)"
RUN cd build && ctest --output-on-failure

FROM ubuntu:22.04 AS runtime
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*
COPY --from=builder /src/build/roguelike_game              /usr/local/bin/roguelike_game
COPY --from=builder /src/build/tests/roguelike_tests      /usr/local/bin/roguelike_tests
COPY --from=builder /src/build/scenarios/                 /usr/local/bin/scenarios/
COPY --from=builder /src/mods /usr/local/bin/mods
WORKDIR /usr/local/bin
ENTRYPOINT ["/usr/local/bin/roguelike_game"]