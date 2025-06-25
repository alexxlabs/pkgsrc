$NetBSD$

solaris adaptation ( types definitions )

--- src/merecat.c.orig	2024-08-14 06:34:51.565703015 +0000
+++ src/merecat.c
@@ -44,6 +44,35 @@
 
 #define SYSLOG_NAMES
 #include <syslog.h>
+#ifdef SYSLOG_NAMES
+#define INTERNAL_INVPRI 0x00    /* Value to indicate no priority in f_pmask */
+#define	INTERNAL_NOPRI	0x10	/* the "no priority" priority */
+				/* mark "facility" */
+#define INTERNAL_ALLPRI 0xFF   /* Value to indicate all priorities in f_pmask */
+#define	INTERNAL_MARK	LOG_MAKEPRI(LOG_NFACILITIES << 3, 0)
+#undef CODE
+typedef struct _code {
+	const char	*c_name;
+	int	c_val;
+} CODE;
+
+CODE prioritynames[] = {
+	{ "alert",	LOG_ALERT },
+	{ "crit",	LOG_CRIT },
+	{ "debug",	LOG_DEBUG },
+	{ "emerg",	LOG_EMERG },
+	{ "err",	LOG_ERR },
+	{ "error",	LOG_ERR },		/* DEPRECATED */
+	{ "info",	LOG_INFO },
+	{ "none",	INTERNAL_NOPRI },	/* INTERNAL */
+	{ "notice",	LOG_NOTICE },
+	{ "panic",	LOG_EMERG },		/* DEPRECATED */
+	{ "warn",	LOG_WARNING },		/* DEPRECATED */
+	{ "warning",	LOG_WARNING },
+	{ "*",		INTERNAL_ALLPRI },	/* INTERNAL */
+	{ NULL,		-1 }
+};
+#endif /* SYSLOG_NAMES */
 
 #include <sys/param.h>
 #include <sys/types.h>
