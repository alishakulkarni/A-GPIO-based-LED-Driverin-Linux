#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <linux/input.h>

void gpio_unexport()
{

	int FDUnexport;
	FDUnexport = open("/sys/class/gpio/unexport", O_WRONLY);
	if (FDUnexport < 0)
	{
    		printf("\n gpio unexport open failed");
	}


//IO PIN 0
	if(0<write(FDUnexport, "11",2))
    		printf("error FdExport 11");
	if(0<write(FDUnexport, "32",2))
    		printf("error FdExport 32");


//IO PIN 1
	write(FDUnexport, "12",2);
	write(FDUnexport, "28",2);
	write(FDUnexport, "45",2);


//IO PIN 2
	write(FDUnexport, "13",2);
	write(FDUnexport, "34",2);
	write(FDUnexport, "77",2);
	write(FDUnexport, "61",2);

//IO PIN 3
	write(FDUnexport, "14",2);
	write(FDUnexport, "16",2);
	write(FDUnexport, "76",2);
	write(FDUnexport, "62",2);

// IO PIN4
	write(FDUnexport, "6",2);
	write(FDUnexport, "36",2);


// IO PIN 5
	write(FDUnexport, "0",2);
	write(FDUnexport, "18",2);
	write(FDUnexport, "66",2);

//IO PIN 6
	write(FDUnexport, "1",2);
	write(FDUnexport, "20",2);
	write(FDUnexport, "68",2);

//IO PIN 7
	write(FDUnexport, "38",2);

//IO PIN 8
	write(FDUnexport, "40",2);


//IO PIN 9
	write(FDUnexport, "4",2);
	write(FDUnexport, "22",2);
	write(FDUnexport, "70",2);


//IO PIN 10
	write(FDUnexport, "10",2);
	write(FDUnexport, "26",2);
	write(FDUnexport, "74",2);

//IO PIN 11
	write(FDUnexport, "5",2);
	write(FDUnexport, "24",2);
	write(FDUnexport, "44",2);


//IO PIN 12
	write(FDUnexport, "15",2);
	write(FDUnexport, "42",2);



//IO PIN 13
	write(FDUnexport, "7",2);
	write(FDUnexport, "30",2);
	write(FDUnexport, "46",2);


//PWM

//IO PIN 3
	write(FDUnexport, "16",2);   
	write(FDUnexport, "17",2);
	write(FDUnexport, "76",2);
	write(FDUnexport, "64",2);
    



//IO PIN 11
	write(FDUnexport, "24",2);  
	write(FDUnexport, "25",2);
	write(FDUnexport, "44",2);
	write(FDUnexport, "72",2);



//IO PIN 9
	write(FDUnexport, "22",2);
	write(FDUnexport, "23",2);  
	write(FDUnexport, "70",2);   


	close(FDUnexport);

}

int main()
{

	gpio_unexport();

	printf("I m out! \n");
	return 0;

}
