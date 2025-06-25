#!/bin/sh
# $Id: getsite.sh,v 1.1.1.1 2002/02/13 09:10:10 abs Exp $
# 
# Determine the correct BASE URL from which to download $DISTFILE

DISTFILE=$1

# here we Determine the correct BASE URL from which to download $DISTFILE

if [ -n "$BASE_URL" ] ; then
	echo $BASE_URL
else
	echo "getsites.sh: Unable to extract BASE_URL" >&2
	exit 2
fi
