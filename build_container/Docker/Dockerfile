FROM gcc:11.4.0 AS builder

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.29.1"

COPY ./build_container/Docker/reinstall-cmake.sh /tmp/

RUN mkdir -p /tmp/WhatNuma
COPY ./WhatNuma/ /tmp/WhatNuma/

RUN ls /tmp/ && ls /tmp/WhatNuma

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends numactl libnuma-dev

RUN mkdir build && cmake -S "/tmp/WhatNuma" -B "/build" \
    && cmake --build "/build"

FROM ubuntu:22.04 AS runtime

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends libnuma-dev libgomp1\
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

COPY --from=builder /build/cores.out .
CMD ["/cores.out"]
