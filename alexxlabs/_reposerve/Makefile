# $NetBSD: Makefile,v 1.8 2024/07/31 18:04:33 pin Exp $

# https://github.com/eburghar/reposerve
# https://github.com/eburghar/reposerve/archive/refs/tags/0.7.0.tar.gz

DISTNAME=	reposerve-0.7.0
CATEGORIES=	alexxlabs

# https://docs.huihoo.com/netbsd/pkgsrc/fixes.html#fixes.fetch
MASTER_SITES=	${MASTER_SITE_GITHUB:=eburghar/}
GITHUB_TAG=	${PKGVERSION_NOREV}
EXTRACT_SUFX= .tar.gz

# If you need to download from a dynamic URL you can set DYNAMIC_MASTER_SITES and a
# 'make fetch' will call files/getsite.sh with the name of each file to download as an argument,
# expecting it to output the URL of the directory from which to download it.
# graphics/ns-cult3d is an example of this usage.
#DYNAMIC_MASTER_SITES=true

MAINTAINER=	pin@NetBSD.org
HOMEPAGE=	https://github.com/eburghar/reposerve
COMMENT=	Simple Alpine linux packages server written in Rust
LICENSE=	mit

# Generate a list of dependencies with:
#	bmake CARGO_ARGS="build --release" build && bmake print-cargo-depends > cargo-depends.mk
# Prepend .include "cargo-depends.mk" to any other .includes.
# Incorporate these modules in distinfo with: 'bmake makesum'
.include "cargo-depends.mk"

#RUST_REQ=	1.79.0
#Upstream does not state the required MSRV.
#This package is confirmed to build with Rust 1.79.0 on amd64
INSTALLATION_DIRS=	${PKGMANDIR}/man1

#post-install:
#	${INSTALL_MAN} ${WRKSRC}/tldr.1 \
#		${DESTDIR}${PREFIX}/${PKGMANDIR}/man1/tldr.1

# If a program is written in Rust and uses Cargo to build,
# have the package include ../../lang/rust/cargo.mk.
.include "../../lang/rust/cargo.mk"
.include "../../mk/bsd.pkg.mk"
