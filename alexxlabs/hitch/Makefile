# $NetBSD: Makefile,v 1.22 2023/10/24 22:10:48 wiz Exp $

# README:	https://www.netbsd.org/docs/pkgsrc/build.html
#			https://github.com/TritonDataCenter/pkgsrc/wiki/pkgdev:signing
#			https://www.perkin.org.uk/posts/pkgsrc-on-smartos-creating-new-packages.html
#			https://docs.huihoo.com/netbsd/pkgsrc/debug.html

DISTNAME=	hitch-1.8.0
# if source name containes things, that do not need to be the actual package name,
# then with 'PKGNAME' we define actual future package name
#PKGNAME=	alx_hitch-1.8.0

# The variable DISTFILES specifies the list of distfiles that have to be fetched.
# Its value defaults to ${DEFAULT_DISTFILES} and its value is ${DISTNAME}${EXTRACT_SUFX},
# so that most packages don't need to define it at all.
# EXTRACT_SUFX is .tar.gz by default, but can be changed freely.
# Note that if your package requires additional distfiles to the default one,
# you cannot just append the additional filenames using the += operator, but you have write for example:
# DISTFILES=      ${DEFAULT_DISTFILES} additional-files.tar.gz
# Each distfile is fetched from a list of sites, usually MASTER_SITES.
# If the package has multiple DISTFILES or multiple PATCHFILES from different sites,
# you can set SITES.distfile to the list of URLs where the file distfile (including the suffix) can be found.
# DISTFILES=      ${DISTNAME}${EXTRACT_SUFX}
# DISTFILES+=     foo-file.tar.gz
# SITES.foo-file.tar.gz= \
#	https://www.somewhere.com/somehow/ \
#	https://www.somewhereelse.com/mirror/somehow/

PKGREVISION=	2
CATEGORIES=	alexxlabs

# When actually fetching the distfiles, each item from MASTER_SITES or SITES.* gets the name of each distfile
# appended to it, *without an intermediate slash*. Therefore, all site values have to end with a slash or other
# separator character. This allows for example to set MASTER_SITES to a URL of a CGI script that gets
# the name of the distfile as a parameter. In this case, the definition would look like:
# MASTER_SITES=   https://www.example.com/download.cgi?file=
# The exception to this rule are URLs starting with a *dash*. In that case the URL is taken as is,
# fetched and the result stored under the name of the distfile. You can use this style for the case when
# the download URL style does not match the above common case. For example, if permanent download URL is
# a redirector to the real download URL, or the download file name is offered by an HTTP Content-Disposition header.
# In the following example, foo-1.0.0.tar.gz will be created instead of the default v1.0.0.tar.gz.
# DISTNAME=		foo-1.0.0
# MASTER_SITES=	-https://www.example.com/archive/v1.0.0.tar.gz
#
# There are some predefined values for MASTER_SITES, which can be used in packages.
# The names of the variables should speak for themselves
# MASTER_SITE_APACHE MASTER_SITE_BACKUP MASTER_SITE_CRATESIO MASTER_SITE_CYGWIN MASTER_SITE_DEBIAN
# MASTER_SITE_FREEBSD MASTER_SITE_FREEBSD_LOCAL MASTER_SITE_GENTOO MASTER_SITE_GITHUB MASTER_SITE_GITLAB
# MASTER_SITE_GNOME MASTER_SITE_GNU MASTER_SITE_GNUSTEP MASTER_SITE_HASKELL_HACKAGE MASTER_SITE_IFARCHIVE
# MASTER_SITE_KDE MASTER_SITE_MOZILLA MASTER_SITE_MOZILLA_ALL MASTER_SITE_MYSQL MASTER_SITE_NETLIB
# MASTER_SITE_OPENBSD MASTER_SITE_OPENOFFICE MASTER_SITE_OSDN MASTER_SITE_PERL_CPAN MASTER_SITE_PGSQL
# MASTER_SITE_PYPI MASTER_SITE_RUBYGEMS MASTER_SITE_R_CRAN MASTER_SITE_SOURCEFORGE MASTER_SITE_SUNSITE
# MASTER_SITE_SUSE MASTER_SITE_TEX_CTAN MASTER_SITE_XCONTRIB MASTER_SITE_XEMACS MASTER_SITE_XORG
#
# If you choose one of these predefined sites, you may want to specify a subdirectory of that site.
# Since these macros may expand to more than one actual site, you must use the following construct
# to specify a subdirectory:
# MASTER_SITES=   ${MASTER_SITE_GNU:=sub/directory/name/}
# MASTER_SITES=   ${MASTER_SITE_SOURCEFORGE:=project_name/}
# Note the trailing slash after the subdirectory name.

MASTER_SITES=	https://hitch-tls.org/source/

# !!! To ensure you have all the source downloaded initially you can run the command:
# % make fetch-list | sh
# which will output and run a set of shell commands to fetch the necessary files into
# the distfiles directory.

# The 'fetch' phase makes sure that all the distfiles exist in a local directory
# (DISTDIR, which can be set by the pkgsrc user). If the files do not exist,
# they are fetched using commands of the form:
#
#${FETCH_CMD} ${FETCH_BEFORE_ARGS} ${site}${file} ${FETCH_AFTER_ARGS}
#
# where ${site} varies through several possibilities in turn: first, MASTER_SITE_OVERRIDE is tried,
# then the sites specified in either SITES.file if defined, else MASTER_SITES or PATCH_SITES,
# as applies, then finally the value of MASTER_SITE_BACKUP. The order of all except the first
# and the last can be optionally sorted by the user, via setting either MASTER_SORT_RANDOM,
# and MASTER_SORT_AWK or MASTER_SORT_REGEX.
# The specific command and arguments used depend on the FETCH_USING parameter. The example above is for
# FETCH_USING=custom. The distfiles mirror run by the NetBSD Foundation uses the mirror-distfiles target
# to mirror the distfiles, if they are freely distributable. Packages setting NO_SRC_ON_FTP
# (usually to '${RESTRICTED}') will not have their distfiles mirrored.
#
# * The checksum phase *
# After the distfile(s) are fetched, their checksum is generated and compared with the checksums stored
# in the distinfo file. If the checksums don't match, the build is aborted. This is to ensure the same
# distfile is used for building, and that the distfile wasn't changed, e.g. by some malign force,
# deliberately changed distfiles on the master distribution site or network lossage.
# !!! To regenerate the distinfo file, use the 'bmake distinfo' command.
#
# * The extract phase *
# When the distfiles are present on the local system, they need to be extracted, as they usually come in the
# form of some compressed archive format. By default, all DISTFILES are extracted. If you only need some of them,
# you can set the EXTRACT_ONLY variable to the list of those files. Extracting the files is usually done by a little
# program, mk/extract/extract, which already knows how to extract various archive formats, so most likely
# you will not need to change anything here. But if you need, the following variables may help you:
#	EXTRACT_OPTS_{BIN,LHA,PAX,RAR,TAR,ZIP,ZOO}
# Use these variables to override the default options for an extract command, which are defined in mk/extract/extract.
#	EXTRACT_USING
# This variable can be set to bsdtar, gtar, nbtar (which is the default value), pax, or an absolute pathname
# pointing to the command with which tar archives should be extracted. It is preferred to choose bsdtar over gtar
# if NetBSD's pax-as-tar is not good enough. If the extract program doesn't serve your needs, you can also override
# the EXTRACT_CMD variable, which holds the command used for extracting the files. This command is executed
# in the ${WRKSRC} directory. During execution of this command, the shell variable 'extract_file' holds
# the absolute pathname of the file that is going to be extracted. And if that still does not suffice,
# you can override the do-extract target in the package Makefile.
#
# * The patch phase *
# After extraction, all the patches named by the PATCHFILES, those present in the patches subdirectory of the package
# as well as in $LOCALPATCHES/$PKGPATH (e.g. /usr/local/patches/graphics/png) are applied.
# Patchfiles ending in .Z or .gz are uncompressed before they are applied, files ending in .orig or .rej are ignored.
# Any special options to patch(1) can be handed in PATCH_DIST_ARGS. See Section 12.3, 'patches/*' for more details.
# By default patch(1) is given special arguments to make it fail if the expected text from the patch context
# is not found in the patched file. If that happens, fix the patch file by comparing it with the actual text
# in the file to be patched.
# --------------------------------------------------------------------------------------------------------
# this is tricky to explain, but let's try and, to put things into context let's do it with a fake-pkg
#
# cd /usr/pkgsrc/fake-pkg
# make
#
# Now, for some reason your build failed and you need to patch a file to make it work,
# let's say the Makefile
#
# cd /workdir/fake-pkg
# pkgvi Makefile
#
# Do your edits to the file and save them.
#
# cd /usr/pkgsrc/fake-pkg
# mkpatches
#
# you should now have a patches folder inside /usr/pkgsrc/fake-pkg
# cd into it and check how many files it contains. Remove the file which contains orig in the name and edit the other one adding a comment as to why the patch is needed. Then,
#
# cd /usr/pkgsrc/fake-pkg
# make clean
# make makepatchsum
#
# Check everything looks fine with pkglint -e, if not correct what's wrong and when happy just
# start the build again.
# --------------------------------------------------------------------------------------------------------
# !!! patches HOWTO
# https://www.netbsd.org/docs/pkgsrc/components.html#components.patches
#
# all package sources extracted and compiled from workingdir:
# /data/chroot/dev-trunk-x86_64/home/pbulk/build/alexxlabs/merecat/work/merecat-2.31/src
# to prepare a patch, do the following:
# after 'bmake fetch' and 'bmake extract' copy extracted sources
# 	from: /data/chroot/dev-trunk-x86_64/home/pbulk/build/alexxlabs/merecat/work/merecat-2.31/src
#	to /data/alexxlabs/src_patches
# to have a backup of sources in case we do 'bmake clean' and clean original workingdir
#
# we recommend using 'mkpatches' to make a whole set of patches.
# You just have to back up files before you edit them to filename.orig, e.g:
# cp -p filename filename.orig
# - after that, do the changes in 'filename', so we have 'filename' and 'filename.orig'
# put ALL this files into workdir and from inside of sandbox environment give the command 'mkpatches'
# patches will be created inside 'patches' subfolder of package sources
# When you have finished a patches procedures, remember to generate the checksums for the patch files
# by using the 'bmake makepatchsum' command
#
#
# * The tools phase *
# https://www.netbsd.org/docs/pkgsrc/tools.html
#
# * The wrapper phase *
# This phase creates wrapper programs for the compilers and linkers. The following variables can be used to tweak
# the wrappers.
#	ECHO_WRAPPER_MSG
# The command used to print progress messages. Does nothing by default. Set to ${ECHO} to see the progress messages.
#
#	WRAPPER_DEBUG
# This variable can be set to yes (default) or no, depending on whether you want additional information
# in the wrapper log file.
#
#	WRAPPER_UPDATE_CACHE
# This variable can be set to yes or no, depending on whether the wrapper should use its cache,
# which will improve the speed. The default value is yes, but is forced to no if the platform does not support it.
#
#	WRAPPER_REORDER_CMDS
# A list of reordering commands. A reordering command has the form reorder:l:lib1:lib2.
# It ensures that that -llib1 occurs before -llib2.
#
# * The configure phase *
# Most pieces of software need information on the header files, system calls, and library routines
# which are available on the platform they run on. The process of determining this information is known
# as configuration, and is usually automated. In most cases, a script is supplied with the distfiles,
# and its invocation results in generation of header files, Makefiles, etc.
#
# If the package contains a configure script, this can be invoked by setting HAS_CONFIGURE to 'yes'.
#
# If the configure script is a GNU autoconf script, you should set GNU_CONFIGURE to 'yes' instead.
#
# In the do-configure stage, a rough equivalent of the following command is run. See mk/configure/configure.mk,
# target do-configure-script for the exact definition.
#
#	.for dir in ${CONFIGURE_DIRS}
#	        cd ${WRKSRC} && cd ${dir} \
#	        && env ${CONFIGURE_ENV} \
#	            ${CONFIG_SHELL} ${CONFIGURE_SCRIPT} ${CONFIGURE_ARGS}
#	.endfor
#
# CONFIGURE_DIRS (default: '.') is a list of pathnames relative to WRKSRC. In each of these directories,
# the configure script is run with the environment CONFIGURE_ENV and arguments CONFIGURE_ARGS.
# The variables CONFIGURE_ENV, CONFIGURE_SCRIPT (default: './configure') and CONFIGURE_ARGS
# may all be changed by the package.
# If the program uses the Perl way of configuration (mainly Perl modules, but not only), i.e. a file
# called Makefile.PL, it should include ../../lang/perl5/module.mk. To set any parameter for Makefile.PL
# use the MAKE_PARAMS variable (e.g., MAKE_PARAMS+=foo=bar
#
# If the program uses an Imakefile for configuration, the appropriate steps can be invoked by setting USE_IMAKE
# to 'yes'. If you only need xmkmf, add it to USE_TOOLS. You can add variables to xmkmf's environment
# by adding them to the SCRIPTS_ENV variable.
#
# If the program uses cmake for configuration, the appropriate steps can be invoked by including
# ../../devel/cmake/build.mk. You can add variables to cmake's environment by adding them to the CONFIGURE_ENV
# variable and arguments to cmake by adding them to the CMAKE_ARGS variable. If you want to add arguments
# only for particular stages, you can use the CMAKE_CONFIGURE_ARGS, CMAKE_BUILD_ARGS, and CMAKE_INSTALL_ARGS variables.
# You can set the CONFIGURE_DIRS variable to the directories in which CMake should be run, relative to WRKSRC.
# This defaults to to '.'
#
# If there is no configure step at all, set NO_CONFIGURE to 'yes'
#
# ======================================================================================================
# * The build phase	*
# For building a package, a rough equivalent of the following code is executed; see mk/build/build.mk,
# target do-build for the exact definition.
#
#	.for dir in ${BUILD_DIRS}
#	        cd ${WRKSRC} && cd ${dir} \
#	        && env ${MAKE_ENV} \
#	            ${MAKE_PROGRAM} ${MAKE_FLAGS} ${BUILD_MAKE_FLAGS} -f ${MAKE_FILE} ${BUILD_TARGET}
#	.endfor
#
# BUILD_DIRS (default: '.') is a list of pathnames relative to WRKSRC. In each of these directories,
# MAKE_PROGRAM is run with the environment MAKE_ENV and arguments BUILD_MAKE_FLAGS.
# The variables MAKE_ENV, BUILD_MAKE_FLAGS, MAKE_FILE and BUILD_TARGET may all be changed by the package.
# The default value of MAKE_PROGRAM is 'gmake' if USE_TOOLS contains 'gmake', 'make' otherwise.
# The default value of MAKE_FILE is 'Makefile', and BUILD_TARGET defaults to 'all'.
# If there is no build step at all, set NO_BUILD to 'yes'.
#
# * The install phase *
# Once the build stage has completed, the final step is to install the software in public directories,
# so users can access the programs and files.
# In the install phase, a rough equivalent of the following code is executed; see mk/install/install.mk,
# target do-install for the exact definition. Additionally, before and after this code, several consistency
# checks are run against the files-to-be-installed, see mk/check/*.mk for details.
#
#	.for dir in ${INSTALL_DIRS}
#	        cd ${WRKSRC} && cd ${dir} \
#	        && env ${INSTALL_ENV} ${MAKE_ENV} \
#	            ${MAKE_PROGRAM} ${MAKE_FLAGS} ${INSTALL_MAKE_FLAGS} \
#	                -f ${MAKE_FILE} ${INSTALL_TARGET}
#	.endfor
#
# The variable's meanings are analogous to the ones in the build phase. INSTALL_DIRS defaults to BUILD_DIRS.
# INSTALL_TARGET is 'install' by default, plus 'install.man' if USE_IMAKE is defined and NO_INSTALL_MANPAGES
# is not defined.
# In the install phase, the following variables are useful. They are all variations of the install(1)
# command that have the owner, group and permissions preset. INSTALL is the plain install command.
# The specialized variants, together with their intended use, are:
#	INSTALL_PROGRAM_DIR directories that contain binaries
#	INSTALL_SCRIPT_DIR directories that contain scripts
#	INSTALL_LIB_DIR directories that contain shared and static libraries
#	INSTALL_DATA_DIR directories that contain data files
#	INSTALL_MAN_DIR directories that contain man pages
#	INSTALL_GAME_DIR directories that contain data files for games
#	INSTALL_PROGRAM binaries that can be stripped from debugging symbols
#	INSTALL_SCRIPT binaries that cannot be stripped
#	INSTALL_GAME game binaries
#	INSTALL_LIB shared and static libraries
#	INSTALL_DATA data files
#	INSTALL_GAME_DATA data files for games
#	INSTALL_MAN man pages
# Some other variables are: INSTALL_UNSTRIPPED
# If set to yes, do not run strip(1) when installing binaries. Any debugging sections and symbols present
# in binaries will be preserved.
#	INSTALLATION_DIRS
# A list of directories relative to PREFIX that are created by pkgsrc at the beginning of the install phase.
# The package is supposed to create all needed directories itself before installing files to it and list
# all other directories here.
# In the rare cases that a package shouldn't install anything, set NO_INSTALL to 'yes'.
# This is mostly relevant for packages in the regress category.
#
# ======================================================================================================
# !!! However, AFTER INSTALL phase
# now that we have a populated DESTDIR, we can use the print-PLIST target to generate it for us:
#	bmake print-PLIST >PLIST
# ======================================================================================================
#
# buildlink
#
# !!! IF we are installing a library package, we should provide a buildlink3.mk file of our own
# so that other packages can depend on us correctly. Again, there is a package that can help with this
# - pkgtools/createbuildlink.
#
# $ createbuildlink >buildlink3.mk
#
# This will create a template file but you should read and edit, removing the lines
# marked with XXX and making any changes they recommend.
# ======================================================================================================
#
# * The package phase*
# Once the install stage has completed, a binary package of the installed files can be built.
# These binary packages can be used for quick installation without previous compilation,
# e.g. by the make bin-install or by using pkg_add.
# By default, the binary packages are created in ${PACKAGES}/All and symlinks are created in ${PACKAGES}/category,
# one for each category in the CATEGORIES variable. PACKAGES defaults to pkgsrc/packages.
#
# * Verify *
# Once we have a working package it's worth doing a couple of checks to make sure everything looks ok:
#	: Check the package listing looks ok
#	$ pkg_info -L augeas
#
#	: View the included DESCR and homepage
#	$ pkg_info -d augeas
#
#	: Check what the package lists as its dependencies
#	$ pkg_info -N augeas
#
# We also should run pkglint (pkgtools/pkglint) which will perform some sanity checks
# on our infrastructure files prior to us importing the package into pkgsrc itself.
# In my case it pointed out some possible issues:
#	$ pkglint -e
# Run "pkglint -fs -e" to show what can be fixed automatically.)
# Run "pkglint -F -e" to automatically fix some issues.
#
MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://hitch-tls.org/
COMMENT=	High performance SSL/TLS proxy
LICENSE=	2-clause-bsd

GNU_CONFIGURE=	yes
USE_TOOLS+=	pkg-config

.include "../../mk/bsd.prefs.mk"

CHECK_PORTABILITY_SKIP+=	src/tests/*

CPPFLAGS.SunOS+=	-D__EXTENSIONS__
LIBS.SunOS+=		-lnsl -lsocket

BUILD_DEFS+=		HITCH_USER HITCH_GROUP HITCH_CERTS VARBASE

HITCH_USER?=		hitch
HITCH_GROUP?=		hitch
HITCH_CERTS?=		${PKG_SYSCONFDIR}/certs.pem
HITCH_OCSP?=		${VARBASE}/db/hitch

PKG_GROUPS+=	${HITCH_GROUP}
PKG_USERS+=	${HITCH_USER}:${HITCH_GROUP}
PKG_GECOS.${HITCH_USER}= hitch daemon user

RCD_SCRIPTS=		hitch

MESSAGE_SUBST+=		HITCH_CERTS=${HITCH_CERTS}

SUBST_CLASSES+=		dir
SUBST_STAGE.dir=	pre-configure
SUBST_FILES.dir=	hitch.conf.example src/configuration.c
SUBST_VARS.dir=		HITCH_USER HITCH_GROUP HITCH_CERTS HITCH_OCSP
SUBST_MESSAGE.dir=	Setting default configuration values

PKG_SYSCONFSUBDIR=	hitch
CONF_FILES+=		share/examples/hitch/hitch.conf.example \
			${PKG_SYSCONFDIR}/hitch.conf

INSTALLATION_DIRS+=	share/examples/hitch

OWN_DIRS_PERMS+=	${HITCH_OCSP} ${HITCH_USER} ${HITCH_GROUP} 0755

post-install:
	${MV} ${DESTDIR}${PREFIX}/share/doc/hitch/hitch.conf.example \
		${DESTDIR}${PREFIX}/share/examples/hitch

# Dependencies in pkgsrc are primarily handled in two ways, either with a 'buildlink' file
# when depending upon shared libraries or particular infrastructure,
# or a simple DEPENDS line to pull in a required package.
#
# EXAMPLE to find needed:
#	Ok, so this package depends upon 'readline'. As that is a library, we are looking
#	for a suitable buildlink3.mk file, and one of the easiest ways to do this is:
#
#	$ ls -1d ../../*/*readline*/buildlink3.mk
#
# To use that file, all we need to do is add an .include line at the bottom of Makefile,
# just above the 'bsd.pkg.mk' include.
#
#	../../devel/readline/buildlink3.mk # include THIS LINE !!!
#
PYTHON_FOR_BUILD_ONLY=	yes
.include "../../lang/python/pyversion.mk"

.include "../../devel/libev/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
