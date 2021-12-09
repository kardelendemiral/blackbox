struct paths{
	char *path1;
	char *path2;
};

program BLACKBOX_PROG{
	version BLACKBOX_VERS{
		int blackbox(paths)=1;
	}=1;
}=0x12345678;