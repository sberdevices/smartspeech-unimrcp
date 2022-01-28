#!/bin/bash

set -eux
set -o pipefail

cd /src
bazel --output_user_root='/bazel-root' build --cxxopt='-std=c++17' //:plugins

mkdir -p output && chmod o+w output
cp bazel-bin/plugin/smartspeech-recognition-plugin.so ./output
cp bazel-bin/plugin/smartspeech-synthesis-plugin.so ./output
