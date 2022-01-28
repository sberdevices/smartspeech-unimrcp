"""
"""

load("//third_party/apple:direct.bzl", "load_bazel_apple")
load("//third_party/protobuf:direct.bzl", "load_protobuf")
load("//third_party/grpc:direct.bzl", "load_grpc")

def load_apple_forward_deps():
  load_bazel_apple()

def load_forward_deps():
  load_protobuf()
  load_grpc()
