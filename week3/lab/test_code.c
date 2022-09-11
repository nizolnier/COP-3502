/*this is a test code to detect memory leak using the provided
leak_detector_c.h and leak_detector_c.c file. Please keept these two files in addition to your code in the same directory.
After running your code, it will produce a leak_info.txt file. The file will be empty if there is no memory leak. Otherwise, the file will contain the memory leak with size and line number.
Enjoy! */
#include	<stdlib.h>
#include	"leak_detector_c.h"
int main()
{
	atexit(report_mem_leak); //add this line to your code
	char * ptr1 = (char *)malloc(10);
	int * ptr2 = (int *)calloc(10, sizeof(int));
	float * ptr3 = (float *) calloc(15, sizeof(float));
	free(ptr1);
	free(ptr2);
	free(ptr3);
	//free(ptr1); //run the code with commenting and uncommenting this line for testing!
	
	return 0;
}
