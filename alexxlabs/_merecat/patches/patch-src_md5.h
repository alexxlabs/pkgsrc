$NetBSD$

solaris adaptation ( types definitions )

--- src/md5.h.orig	2024-08-14 06:34:51.566439961 +0000
+++ src/md5.h
@@ -20,19 +20,19 @@
 #define	MD5_DIGEST_STRING_LENGTH	(MD5_DIGEST_LENGTH * 2 + 1)
 
 typedef struct MD5Context {
-	u_int32_t state[4];			/* state */
-	u_int64_t count;			/* number of bits, mod 2^64 */
-	u_int8_t buffer[MD5_BLOCK_LENGTH];	/* input buffer */
+	uint32_t state[4];			/* state */
+	uint64_t count;			/* number of bits, mod 2^64 */
+	uint8_t buffer[MD5_BLOCK_LENGTH];	/* input buffer */
 } MD5_CTX;
 
 void	 MD5Init(MD5_CTX *);
-void	 MD5Update(MD5_CTX *, const u_int8_t *, size_t);
+void	 MD5Update(MD5_CTX *, const uint8_t *, size_t);
 void	 MD5Pad(MD5_CTX *);
-void	 MD5Final(u_int8_t [MD5_DIGEST_LENGTH], MD5_CTX *);
-void	 MD5Transform(u_int32_t [4], const u_int8_t [MD5_BLOCK_LENGTH]);
+void	 MD5Final(uint8_t [MD5_DIGEST_LENGTH], MD5_CTX *);
+void	 MD5Transform(uint32_t [4], const uint8_t [MD5_BLOCK_LENGTH]);
 char	*MD5End(MD5_CTX *, char *);
 char	*MD5File(const char *, char *);
 char	*MD5FileChunk(const char *, char *, off_t, off_t);
-char	*MD5Data(const u_int8_t *, size_t, char *);
+char	*MD5Data(const uint8_t *, size_t, char *);
 
 #endif /* _MD5_H_ */
