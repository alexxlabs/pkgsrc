$NetBSD$

solaris adaptation ( types definitions )

--- src/libhttpd.c.orig	2016-11-05 19:38:51.000000000 +0000
+++ src/libhttpd.c
@@ -624,7 +624,7 @@ send_mime(httpd_conn *hc, int status, ch
 			MD5_CTX md5_ctx;
 
 			MD5Init(&md5_ctx);
-			MD5Update(&md5_ctx, (const u_int8_t *)hc->file_address, length);
+			MD5Update(&md5_ctx, (const uint8_t *)hc->file_address, length);
 			MD5Final(digest, &md5_ctx);
 			my_snprintf(etagbuf, sizeof(etagbuf),
 				    "ETag: \"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\"\r\n",
@@ -2519,11 +2519,17 @@ static int child_ls_read_names(httpd_con
 	static size_t maxencrname = 0;
 
 	while ((de = readdir(dirp))) {
-		if (onlydir && de->d_type != DT_DIR)
+		/*if (onlydir && de->d_type != DT_DIR)
 			continue;
 		if (!onlydir && de->d_type == DT_DIR) 
-			continue;
-			
+			continue; */
+
+		/* start_my_fix */
+		if (onlydir) continue;
+		if (!onlydir) continue;
+		/* end_my_fix */
+
+
 		if (nnames >= maxnames) {
 			if (maxnames == 0) {
 				maxnames = 100;
