"""
Transitive dependencies for apr
"""

load("//contrib/rules_foreign_cc:transitive.bzl", "load_rules_foreign_cc_transitive_dependencies")

def load_apr_transitive_dependencies():
    load_rules_foreign_cc_transitive_dependencies()
