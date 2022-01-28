"""
"""

load("//third_party/apple:transitive.bzl", "load_bazel_apple_deps")
load("//third_party/protobuf:transitive.bzl", "load_protobuf_deps")
load("//third_party/grpc:transitive.bzl", "load_grpc_deps")

def load_apple_backward_deps():
  load_bazel_apple_deps()

def load_backward_deps():
  load_protobuf_deps()
  load_grpc_deps()
