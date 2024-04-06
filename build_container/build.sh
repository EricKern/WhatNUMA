#!/bin/bash

# Define your variables
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
echo $SCRIPT_DIR

IMAGE_NAME="your_image_name:first"
DOCKERFILE_PATH="${SCRIPT_DIR}/Docker/Dockerfile"
BUILD_CONTEXT="${SCRIPT_DIR}/.."

# Build the Docker image
docker build -t "$IMAGE_NAME" -f "$DOCKERFILE_PATH" "$BUILD_CONTEXT"
