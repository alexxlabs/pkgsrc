# $NetBSD: options.mk,v 1.2 2019/04/23 06:04:41 nia Exp $

# https://www.netbsd.org/docs/pkgsrc/configuring.html | 6.7. Selecting Build Options
# https://wiki.netbsd.org/pkgsrc/how_to_use_pkg_options_with_pkgsrc/

# bmake show-options

PKG_OPTIONS_VAR=	PKG_OPTIONS.forgejo
PKG_SUPPORTED_OPTIONS=	sqlite bindata

# Build a single monolithic binary, with all assets included. Required for production build.
PKG_SUGGESTED_OPTIONS= bindata
# Bundling all assets (JS/CSS/templates, etc) into the binary.
# Using the 'bindata' build tag is required for production deployments.
# You could exclude bindata when you are developing/testing Gitea
# or able to separate the assets correctly.

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Msqlite)
GO_TAGS+=	sqlite sqlite_unlock_notify
.include "../../databases/sqlite3/buildlink3.mk"
.endif

.if !empty(PKG_OPTIONS:Mbindata)
GO_TAGS+=	bindata
.endif

#       PKG_OPTIONS_VAR (must be defined)
#               The variable the user can set to enable or disable
#               options specifically for this package.
#
#       PKG_SUPPORTED_OPTIONS
#               This is a list of build options supported by the package.
#               This variable should be set in a package Makefile.  E.g.,
#
#                       PKG_SUPPORTED_OPTIONS=  kerberos ldap ssl
#
#       PKG_OPTIONS_OPTIONAL_GROUPS
#               This is a list of names of groups of mutually exclusive
#               options.  The options in each group are listed in
#               PKG_OPTIONS_GROUP.<groupname>.  The most specific
#               setting of any option from the group takes precedence
#               over all other options in the group.  Options from
#               the groups will be automatically added to
#               PKG_SUPPORTED_OPTIONS.
#
#       PKG_OPTIONS_REQUIRED_GROUPS
#               Like PKG_OPTIONS_OPTIONAL_GROUPS, but building
#               the packages will fail if no option from the group
#               is selected.
#
#       PKG_OPTIONS_NONEMPTY_SETS
#              This is a list of names of sets of options.  At
#              least one option from each set must be selected.
#              The options in each set are listed in
#              PKG_OPTIONS_SET.<setname>.  Options from the sets
#              will be automatically added to PKG_SUPPORTED_OPTIONS.
#
#       PKG_SUGGESTED_OPTIONS (defaults to empty)
#               This is a list of build options which are enabled by default.
#
#       PKG_OPTIONS_LEGACY_VARS
#               This is a list of USE_VARIABLE:option pairs that
#               map legacy /etc/mk.conf variables to their option
#               counterparts.
#
#       PKG_OPTIONS_LEGACY_OPTS
#               This is a list of old-option:new-option pairs that
#               map options that have been renamed to their new
#               counterparts.
#
#       PKG_LEGACY_OPTIONS
#               A list of options implied by deprecated variables
#               used.  This can be used for cases that neither
#               PKG_OPTIONS_LEGACY_VARS nor PKG_OPTIONS_LEGACY_OPTS
#               can handle, e.g., when PKG_OPTIONS_VAR is renamed.
#
#       PKG_OPTIONS_DEPRECATED_WARNINGS
#               A list of warnings about deprecated variables or
#               options used, and what to use instead.
#
#       If none of PKG_SUPPORTED_OPTIONS, PKG_OPTIONS_OPTIONAL_GROUPS,
#       PKG_OPTIONS_REQUIRED_GROUPS, and PKG_OPTIONS_NONEMPTY_SETS are
#       defined, PKG_OPTIONS is set to the empty list and the package
#       is otherwise treated as not using the options framework.
#
#
# Optionally, the user may define the following variables in /etc/mk.conf:
#
#       PKG_DEFAULT_OPTIONS
#               This variable can be used to override default
#               options for every package.  Options listed in this
#               variable will be enabled in every package that
#               supports them.  If you prefix an option with `-',
#               it will be disabled in every package.
#
#       ${PKG_OPTIONS_VAR}
#               This variable can be used to override default
#               options and options listed in PKG_DEFAULT_OPTIONS.
#               The syntax is the same as PKG_DEFAULT_OPTIONS.
#
# After including this file, the following variables are defined:
#
#       PKG_OPTIONS
#               This is the list of the selected build options, properly
#               filtered to remove unsupported and duplicate options.
#
#       PKG_DISABLED_OPTIONS
#               This is the list of the disabled build options; this is
#               the complement of PKG_OPTIONS.
