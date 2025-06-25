$NetBSD$

solaris adaptation ( types definitions )

--- src/md5.c.orig	2024-08-14 06:34:51.561223348 +0000
+++ src/md5.c
@@ -37,7 +37,7 @@
 	(cp)[1] = (value) >> 8;						\
 	(cp)[0] = (value); } while (0)
 
-static u_int8_t PADDING[MD5_BLOCK_LENGTH] = {
+static uint8_t PADDING[MD5_BLOCK_LENGTH] = {
 	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
@@ -71,7 +71,7 @@ MD5Update(MD5_CTX *ctx, const unsigned c
 	need = MD5_BLOCK_LENGTH - have;
 
 	/* Update bitcount */
-	ctx->count += (u_int64_t)len << 3;
+	ctx->count += (uint64_t)len << 3;
 
 	if (len >= need) {
 		if (have != 0) {
@@ -102,7 +102,7 @@ MD5Update(MD5_CTX *ctx, const unsigned c
 void
 MD5Pad(MD5_CTX *ctx)
 {
-	u_int8_t count[8];
+	uint8_t count[8];
 	size_t padlen;
 
 	/* Convert count to 8 bytes in little endian order. */
@@ -150,19 +150,19 @@ MD5Final(unsigned char digest[MD5_DIGEST
  * the data and converts bytes into longwords for this routine.
  */
 void
-MD5Transform(u_int32_t state[4], const u_int8_t block[MD5_BLOCK_LENGTH])
+MD5Transform(uint32_t state[4], const uint8_t block[MD5_BLOCK_LENGTH])
 {
-	u_int32_t a, b, c, d, in[MD5_BLOCK_LENGTH / 4];
+	uint32_t a, b, c, d, in[MD5_BLOCK_LENGTH / 4];
 
 #if BYTE_ORDER == LITTLE_ENDIAN
 	memcpy(in, block, sizeof(in));
 #else
 	for (a = 0; a < MD5_BLOCK_LENGTH / 4; a++) {
-		in[a] = (u_int32_t)(
-		    (u_int32_t)(block[a * 4 + 0]) |
-		    (u_int32_t)(block[a * 4 + 1]) <<  8 |
-		    (u_int32_t)(block[a * 4 + 2]) << 16 |
-		    (u_int32_t)(block[a * 4 + 3]) << 24);
+		in[a] = (uint32_t)(
+		    (uint32_t)(block[a * 4 + 0]) |
+		    (uint32_t)(block[a * 4 + 1]) <<  8 |
+		    (uint32_t)(block[a * 4 + 2]) << 16 |
+		    (uint32_t)(block[a * 4 + 3]) << 24);
 	}
 #endif
 
