# $NetBSD$

# get fron here: https://github.com/NetBSD/pkgsrc-wip/tree/master/forgejo
# TODO: maybe try this: https://github.com/TritonDataCenter/pkgsrc-wip/blob/master/forgejo/Makefile

# -------------------------------------------------------------------------------------------------
# - bmake fetch
#
# - create empty PLIST and refresh sizes and hashsums:
#	touch PLIST
#	bmake distinfo
#
# - bmake extract
#
# - create 'go-modules.mk':
#	bmake show-go-modules > go-modules.mk
#
# - try to:
#	bmake
#
# if success...
#
# - try to:
#	bmake package
#
# there is error because dist files not presented in PLIST:
#
# -refresh PLIST:
#	bmake print-PLIST > PLIST
#
# - recompile all again:
#	bmake clean
#	bmake package
#
# - check for errors:
#	pkglint -e
# -------------------------------------------------------------------------------------------------
DISTNAME=	forgejo-src-8.0.2
PKGNAME=	${DISTNAME:S/-src//}
CATEGORIES=	alexxlabs
MASTER_SITES=	https://codeberg.org/forgejo/forgejo/releases/download/v${DISTNAME:S/forgejo-src-//}/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://forgejo.org/
COMMENT=	Git hosting software
LICENSE=	mit

FORGEJO_USER?=	git
FORGEJO_GROUP?=	git
# Further specification of user details may be done by setting per-user variables:
# - PKG_UID.user is the numeric UID for the user.
# - PKG_GECOS.user is the user’s description or comment.
# - PKG_HOME.user is the user’s home directory, and defaults to /nonexistent if not specified.
# - PKG_SHELL.user is the user’s shell, and defaults to /sbin/nologin if not specified
PKG_UID.${FORGEJO_USER}= 1199
PKG_GECOS.${FORGEJO_USER}= forgejo daemon user
PKG_HOME.${FORGEJO_USER}= ${VARBASE}/db/forgejo
PKG_SHELL.${FORGEJO_USER}=	${SH}

#PKG_DEBUG_LEVEL= 1

# Configuration files
# There are two principles that govern the handling of configuration files in pkgsrc:
# - first, the user's configuration must not be lost or overwritten by upgrades or reinstallations;
# - second, the default configuration should always be available for reference.
# To that end, pkgsrc has a framework specifically for handling configuration files.
# In general, configuration files are installed into ${PREFIX}/share/examples,
# and copied from there to the pertinent etc directory as a separate step and only as needed.
#
# To make this work, there are three things that need to happen, any of which may require patching.
# First, the package must be told to read its configuration from the correct place at runtime;
#	this place is ${PKG_SYSCONFDIR} (or possibly a subdirectory of it) which is often but not always ${PREFIX}/etc.
# Second, the package must be taught to install its default configuration files in ${PREFIX}/share/examples/${PKGBASE};
#	this is the point at which patching often becomes required because it is not the same place as the runtime
#	location.
# Third, the configuration files need to be declared in the package makefile; this is the easy part.
#
# With those elements in place, the right things will happen:
# the package install phase and resulting binary package will not touch ${PKG_SYSCONFDIR},
# and the default configuration will be copied into place by the pkgsrc framework only if not already present.
# Similarly, upon deinstall the configuration will not be removed if it has been modified.
# (This means that in the case of reinstallation and upgrades, unmodified configuration files are updated
# but modifications are never discarded.)
#
# As said before, the PKG_SYSCONFDIR variable specifies where configuration files shall be installed. Its
# contents are set based upon the following variables:
# - PKG_SYSCONFBASE: The configuration’s root directory. Defaults to ${PREFIX}/etc although it may
#		be overridden by the user to point to their preferred location (e.g., /etc, /etc/pkg, etc.).
#		Packages must not use it directly.
# - PKG_SYSCONFSUBDIR: A subdirectory of PKG_SYSCONFBASE under which the configuration files for
#		the package being built shall be installed. The definition of this variable only makes sense in the
#		package’s Makefile (i.e., it is not user-customizable).
#		As an example, consider the Apache package, www/apache24, which places its configuration files
#		under the httpd/ subdirectory of PKG_SYSCONFBASE. This should be set in the package Makefile.
# - PKG_SYSCONFVAR: Specifies the name of the variable that holds this package’s configuration directory
#		(if different from PKG_SYSCONFBASE). It defaults to PKGBASE's value,
#		and is always prefixed with	PKG_SYSCONFDIR.
# - PKG_SYSCONFDIR.${PKG_SYSCONFVAR}: Holds the directory where the configuration files for the
#		package identified by PKG_SYSCONFVAR's shall be placed.
#
# Based on the above variables, pkginstall determines the value of PKG_SYSCONFDIR, which is the only
# variable that may be used within a package to refer to its configuration directory.
# The algorithm used to set its value is basically the following:
# 1. If PKG_SYSCONFDIR.${PKG_SYSCONFVAR} is set, its value is used.
# 2. If the previous variable is not defined but PKG_SYSCONFSUBDIR is set in the package’s Makefile,
#		the resulting value is ${PKG_SYSCONFBASE}/${PKG_SYSCONFSUBDIR}.
# 3. Otherwise, it is set to ${PKG_SYSCONFBASE}.
#
# It is worth mentioning that ${PKG_SYSCONFDIR} is automatically added to OWN_DIRS.
# This causes it to be automatically created if needed. See Section 20.1.1 for further details.
# This does not apply to subdirectories of ${PKG_SYSCONFDIR};
# they must be manually created with OWN_DIRS or MAKE_DIRS.
#
# 20.2.4. Declaring configuration files
# Once the required configuration files are in place (i.e., under the examples hierarchy), the pkginstall
# framework can use them as reference copies during the package installation to update what is in
# ${PKG_SYSCONFDIR}. To achieve this, the variables CONF_FILES and CONF_FILES_PERMS are used.
# Check out Section 20.1.2 for further information about their syntax and their purpose. Here is an
# example, taken from the mail/mutt package:
#	EGDIR= ${PREFIX}/share/examples/mutt
#	CONF_FILES= ${EGDIR}/Muttrc ${PKG_SYSCONFDIR}/Muttrc
# Note that (as in the previous section’s example) the EGDIR variable is specific to the package and has no
# meaning outside it.
# For reference, the complete example from Mutt is as follows:
#	CONFIGURE_ARGS+= --sysconfdir=${PKG_SYSCONFDIR}
#	EGDIR= ${PREFIX}/share/examples/mutt
#	CONF_FILES= ${EGDIR}/Muttrc ${PKG_SYSCONFDIR}/Muttrc
#	INSTALLATION_DIRS+= ${EGDIR}
#	INSTALL_MAKE_FLAGS= ${MAKE_FLAGS} sysconfdir=${EGDIR}

EGDIR= ${PREFIX}/share/examples/forgejo
PKG_SYSCONFSUBDIR=	forgejo

CONF_FILES+= ${EGDIR}/app.ini.sample ${PKG_SYSCONFDIR}/app.ini
CONF_FILES_PERMS+=	${EGDIR}/app.ini.sample ${PKG_SYSCONFDIR}/app.ini ${FORGEJO_USER} ${REAL_ROOT_GROUP} 0600

INSTALLATION_DIRS+= ${EGDIR}
INSTALLATION_DIRS+= ${PKG_SYSCONFDIR}
INSTALLATION_DIRS+= ${PREFIX}/bin

# 'MAKE_DIRS' and 'OWN_DIRS' contain a list of directories that should be created and should attempt to be
# destroyed by the installation scripts.
# The difference between the two is that the 'OWN_DIRS' prompts the administrator to remove any directories
# that may be left after deinstallation (because they were not empty),
# while the 'MAKE_DIRS' does not. Example: MAKE_DIRS+= ${VARBASE}/foo/private
OWN_DIRS+=	${PREFIX}/bin
OWN_DIRS+=	${PREFIX}/share/forgejo
OWN_DIRS+=	${PKG_SYSCONFDIR}
OWN_DIRS+=	${VARBASE}/log/forgejo
OWN_DIRS+=	${VARBASE}/db/forgejo
OWN_DIRS+=	${VARBASE}/db/forgejo/custom
OWN_DIRS+=	${EGDIR}

# 'MAKE_DIRS_PERMS' and 'OWN_DIRS_PERMS' contain a list of tuples describing which directories
# should be created and should attempt to be destroyed by the installation scripts. Each tuple holds the
# following values, separated by spaces: the directory name, its owner, its group and its numerical mode.
# For example:
#	MAKE_DIRS_PERMS+= ${VARBASE}/foo/private ${REAL_ROOT_USER} ${REAL_ROOT_GROUP} 0700
# The difference between the two is exactly the same as their non-PERMS counterparts.
OWN_DIRS_PERMS+=	${PREFIX}/bin ${FORGEJO_USER} ${FORGEJO_GROUP} 0755
OWN_DIRS_PERMS+=	${PREFIX}/share/forgejo ${FORGEJO_USER} ${FORGEJO_GROUP} 0700
OWN_DIRS_PERMS+=	${PKG_SYSCONFDIR} ${FORGEJO_USER} ${REAL_ROOT_GROUP} 0755
OWN_DIRS_PERMS+=	${VARBASE}/log/forgejo ${FORGEJO_USER} ${FORGEJO_GROUP} 0700
OWN_DIRS_PERMS+=	${VARBASE}/db/forgejo ${FORGEJO_USER} ${FORGEJO_GROUP} 0700
OWN_DIRS_PERMS+=	${VARBASE}/db/forgejo/custom ${FORGEJO_USER} ${FORGEJO_GROUP} 0770
OWN_DIRS_PERMS+=	${EGDIR} ${FORGEJO_USER} ${FORGEJO_GROUP} 0700

.include "../../lang/go/go-vars.mk"
.include "options.mk"

BUILD_DEFS+=	VARBASE FORGEJO_USER FORGEJO_GROUP

EXTRACT_USING=	bsdtar
USE_TOOLS+=	ggrep gmake pax tar
DEPENDS+=	git-base-[0-9]*:../../devel/git-base

# If a package needs to create special users and/or groups during installation,
# it can do so by using the pkginstall framework.
# Users can be created by adding entries to the PKG_USERS variable.
# Each entry has the following syntax: 'user:group'
PKG_USERS+=	${FORGEJO_USER}:${FORGEJO_GROUP}
# Similarly, groups can be created by adding entries to the PKG_GROUPS variable, whose syntax is: 'group'
PKG_GROUPS+=	${FORGEJO_GROUP}
#	A list of variables that hold bare group names, e.g FORGEJO_GROUP, etc.
PKG_GROUPS_VARS+=	FORGEJO_GROUP
#	A list of variables that hold bare user names, e.g FORGEJO_USER, etc.
PKG_USERS_VARS+=	FORGEJO_USER

# !!! System startup scripts ???
# System startup scripts are special files because they must be installed in a place known by the underlying
# OS, usually outside the installation prefix. Therefore, the same rules described in Section 20.1 apply, and
# the same solutions can be used. However, pkginstall provides a special mechanism to handle these files.
# In order to provide system startup scripts, the package has to:
# 1. Store the script inside ${FILESDIR}, with the .sh suffix appended. Considering the
#	print/cups-base package as an example, it has a cupsd.sh in its files directory.
# 2. Tell pkginstall to handle it, appending the name of the script, without its extension, to the
#	RCD_SCRIPTS variable. Continuing the previous example: RCD_SCRIPTS+= cupsd
# Once this is done, pkginstall will do the following steps for each script in an automated fashion:
# 1. Process the file found in the files directory applying all the substitutions described in the
#	'FILES_SUBST' variable.
# 2. Copy the script from the files directory to the examples hierarchy,
#	${PREFIX}/share/examples/rc.d/. Note that this reference file must be explicitly registered in the PLIST.
# 3. Add code to the installation scripts to copy the startup script from the examples hierarchy into the
#	system-wide startup scripts directory.
#
RCD_SCRIPTS+=	forgejo

# The substitutions are applied immediately after the distfiles are extracted.
# Running bmake extract on the package will leave no traces of the original files.
FILES_SUBST+=	FORGEJO_USER=${FORGEJO_USER}
FILES_SUBST+=	FORGEJO_GROUP=${FORGEJO_GROUP}
# this standard vars do not need to define here,
# they substitute by default ( see manifest.xml )
#FILES_SUBST+=	VARBASE=${VARBASE}
#FILES_SUBST+=	PKG_SYSCONFDIR=${PKG_SYSCONFDIR}

SUBST_CLASSES+=                 fix-app-ini
SUBST_STAGE.fix-app-ini=        pre-configure
SUBST_MESSAGE.fix-app-ini=      Fix app.ini vars.
SUBST_FILES.fix-app-ini=        ${WRKDIR}/app.ini.sample
SUBST_VARS.fix-app-ini=         PKG_SYSCONFDIR VARBASE FORGEJO_USER

pre-patch:
	${CP} ${FILESDIR}/app.ini.sample ${WRKDIR}/
	${ECHO} ${PKGVERSION_NOREV} > ${WRKSRC}/VERSION

# !!! DEBUG - To see the value of a single variable, run: bmake show-var VARNAME=MAKE_ENV
# To see the values of the most common variables, run: 'bmake show-all'
# These variables are grouped by topic.
# To see the variables for a single topic, run: 'bmake show-all-topic',
# for example: 'bmake show-all-build'
#				bmake show-var VARNAME=LDFLAGS

do-build:
	cd ${WRKSRC} && TAGS="${GO_TAGS}" make build

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/gitea ${DESTDIR}${PREFIX}/bin/forgejo

# files/*
# If you have any files that you wish to be placed in the package prior to configuration or building,
# you can place these files here and use a ${CP} command in the 'post-extract' target to achieve this.
#post-extract:
#	${CP} files/app.ini.sample ${WRKSRC}/custom/conf/app.example.ini

post-install:
	${INSTALL_DATA_DIR} ${DESTDIR}${EGDIR}
	${INSTALL_DATA} ${WRKDIR}/app.ini.sample ${DESTDIR}${EGDIR}

.include "go-modules.mk"

.include "../../lang/go/go-module.mk"

# The order in bsd.prefs.mk
# The very first action in bsd.prefs.mk is to define some essential variables like OPSYS,
# OS_VERSION and MACHINE_ARCH.
# Then, the user settings are loaded from the file specified in MAKECONF, which is usually mk.conf. After
# that, those variables that have not been overridden by the user are loaded from mk/defaults/mk.conf.
# After the user settings, the system settings and platform settings are loaded,
# which may override the user settings.
# Then, the tool definitions are loaded. The tool wrappers are not yet in effect. This only happens when
# building a package, so the proper variables must be used instead of the direct tool names.
# As the last steps, some essential variables from the wrapper and the package system flavor are loaded, as
# well as the variables that have been cached in earlier phases of a package build.
.include "../../mk/bsd.prefs.mk"

# The order in bsd.pkg.mk
# First, bsd.prefs.mk is loaded. [ !!! checked !!! NOT LOADED. We need to load it SEPARATELY]
# Then, the various *-vars.mk files are loaded, which fill default values for those variables that have not
# been defined by the package. These variables may later be used even in unrelated files.
# Then, the file bsd.pkg.error.mk provides the target error-check that is added as a special
# dependency to all other targets that use DELAYED_ERROR_MSG or DELAYED_WARNING_MSG.
# Then, the package-specific hacks from hacks.mk are included.
# Then, various other files follow. Most of them don’t have any dependencies on what they need to have
# included before or after them, though some do.
# The code to check PKG_FAIL_REASON and PKG_SKIP_REASON is then executed,
# which restricts the use of these variables to all the files that have been included before.
# Appearances in later files will be silently ignored.
# Then, the files for the main targets are included, in the order of later execution,
# though the actual order should not matter.
# At last, some more files are included that don’t set any interesting variables
# but rather just define make targets to be executed.
.include "../../mk/bsd.pkg.mk"
