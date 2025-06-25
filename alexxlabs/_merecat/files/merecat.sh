#!@RCD_SCRIPTS_SHELL@
#
# $NetBSD: merecat.sh,v 1.1 2024/08/14 17:15:35 fhajny Exp $
#

# PROVIDE: merecat
# REQUIRE: LOGIN

. /etc/rc.subr

name="merecat"
rcvar=$name
command="@PREFIX@/sbin/merecat"
command_args="-f @PKG_SYSCONFDIR@/merecat.conf"
required_files="@PKG_SYSCONFDIR@/merecat.conf"

load_rc_config $name
run_rc_command "$1"
