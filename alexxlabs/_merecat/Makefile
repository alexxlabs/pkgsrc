# $NetBSD$

DISTNAME=	merecat-2.31
CATEGORIES=	alexxlabs
MASTER_SITES=	${MASTER_SITE_GITHUB:=troglobit/merecat/releases/download/v2.31/}
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/troglobit/merecat
COMMENT=	Small and made easy HTTP/HTTPS server based on Jef Poskanzer thttpd
LICENSE=	2-clause-bsd

GNU_CONFIGURE=	yes
USE_TOOLS+=	pkg-config

.include "../../mk/bsd.prefs.mk"

CPPFLAGS.SunOS+=	-D__EXTENSIONS__
LIBS.SunOS+=		-lsocket -lnsl

RCD_SCRIPTS=		merecat

CONF_FILES+=		etc/merecat.conf \
					${PKG_SYSCONFDIR}/merecat.conf

# Merecat depends on a few external libraries, if enabled, e.g:
.include "../../security/openssl/buildlink3.mk" # OpenSSL
.include "../../devel/zlib/buildlink3.mk"		# zlib
.include "../../devel/confuse/buildlink3.mk"	# libConfuse

.include "../../mk/bsd.pkg.mk"
