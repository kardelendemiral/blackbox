struct arguments{
	int num1;
	int num2;
	char path[200];
};

program BLACKBOX_PROG{
	version BLACKBOX_VERS{
		string blackbox(arguments)=1;
	}=1;
}=0x12345678;