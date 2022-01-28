"""
load("//third_party:forward.bzl", "load_apple_forward_deps")
load_apple_forward_deps()
load("//third_party:forward.bzl", "load_forward_deps")
load_forward_deps()

load("//third_party:backward.bzl", "load_apple_backward_deps")
load_apple_backward_deps()
load("//third_party:backward.bzl", "load_backward_deps")
load_backward_deps()
"""

# load("//third_party/openssl:direct.bzl", "load_openssl")
load("//third_party/boringssl:direct.bzl", "load_boringssl")
load_boringssl()


##### Protobuf Rules for Bazel
##### See https://github.com/bazelbuild/rules_proto
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_proto",
    sha256 = "66bfdf8782796239d3875d37e7de19b1d94301e8972b3cbd2446b332429b4df1",
    strip_prefix = "rules_proto-4.0.0",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/refs/tags/4.0.0.tar.gz",
        "https://github.com/bazelbuild/rules_proto/archive/refs/tags/4.0.0.tar.gz",
    ],
)

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_dependencies()
rules_proto_toolchains()

##### gRPC Rules for Bazel
##### See https://github.com/grpc/grpc/blob/master/src/cpp/README.md#make
http_archive(
    name = "com_github_grpc_grpc",
    url = "https://github.com/grpc/grpc/archive/b0f37a22bbae12a4b225a88be6d18d5e41dce881.tar.gz",
    strip_prefix = "grpc-b0f37a22bbae12a4b225a88be6d18d5e41dce881",
)
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
# Not mentioned in official docs... mentioned here https://github.com/grpc/grpc/issues/20511
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()


load("//third_party/rules_foreign_cc:direct.bzl", "load_rules_foreign_cc")
load_rules_foreign_cc()


load("//third_party/nlohmann:direct.bzl", "load_nlohmann")
load_nlohmann()

load("//third_party/zlib:direct.bzl", "load_zlib")
load("//third_party/curl:direct.bzl", "load_curl")

http_archive(
  name = "rules_perl",
  sha256 = "765e6a282cc38b197a6408c625bd3fc28f3f2d44353fb4615490a6eb0b8f420c",
  strip_prefix = "rules_perl-e3ed0f1727d15db6c5ff84f64454b9a4926cc591",
  url = "https://github.com/bazelbuild/rules_perl/archive/e3ed0f1727d15db6c5ff84f64454b9a4926cc591.tar.gz",
)

load_zlib()
load_curl()

load("//third_party/apr:direct.bzl", "load_apr")
load("//third_party/apr-util:direct.bzl", "load_apr_util")
load("//third_party/sofia-sip:direct.bzl", "load_sofia_sip")
load("//third_party/unimrcp:direct.bzl", "load_unimrcp")

load_apr()
load_apr_util()
load_sofia_sip()
load_unimrcp()

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()

load("@rules_perl//perl:deps.bzl", "perl_register_toolchains", "perl_rules_dependencies")
perl_rules_dependencies()
perl_register_toolchains()

