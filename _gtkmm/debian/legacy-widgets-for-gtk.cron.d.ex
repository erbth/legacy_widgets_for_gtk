#
# Regular cron jobs for the legacy-widgets-for-gtk package
#
0 4	* * *	root	[ -x /usr/bin/legacy-widgets-for-gtk_maintenance ] && /usr/bin/legacy-widgets-for-gtk_maintenance
