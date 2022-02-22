load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

LIB_NAME = "apr"

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

configure_make(
    name = "apr",
    configure_in_place = True,
    configure_options = [
      "--disable-shared",
    ],
    env = select({
        "@platforms//os:macos": {"AR": ""},
        "//conditions:default": {},
    }),
    copts = ["-fPIC"],
    lib_name = LIB_NAME,
    lib_source = ":all_srcs",
    out_static_libs = ["libapr-1.a"],
    visibility = ["//visibility:public"],
)
