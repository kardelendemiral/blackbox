struct arguments{
	int num1;
	int num2;
	char path[256];
};

program PART_B_PROG{
	version PART_B_VERS{
		string part_b(arguments)=1;
	}=1;
}=0x12345678;