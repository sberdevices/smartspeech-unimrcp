
"""
Transitive dependencies for unimrcp
"""

load("//third_party/rules_foreign_cc:transitive.bzl", "load_rules_foreign_cc_transitive_dependencies")

def load_apr_util_transitive_dependencies():
    load_rules_foreign_cc_transitive_dependencies()