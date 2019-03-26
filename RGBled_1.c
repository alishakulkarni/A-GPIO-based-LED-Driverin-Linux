#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <linux/input.h>
#include <pthread.h>
#define MOUSE_DEV "/dev/input/mice"

//struct to store GPIO corresponding to user's input. this will be passed to the LED_Blink thread which is responsible for blinking LED in the right order
struct LEDs{

char red[50];
char green[50];
char blue[50];
};

/*2D array to store Linux's GPIO and MUX's GPIO corresponding to a pin.
{0, 11} = For pin 0 (all pins are at index 0), gpio11 is the linux pin (all linux pins are ar index 1)
{1, 12, 45} = For pin 1, gpio12 is the linux pin, 45 is the mux pin (all mux pins are at index 2)
{3, 14, 76, 64} = For pin 2, gpio 14 is the linux pin, 76 is the mux pin and 64 is the mux2_pin (all mux2 pins are at index 3)*/

int pin_data[14][4] = {{ 0, 11 },{ 1, 12, 45 }, { 2, 13, 77 }, { 3, 14, 76, 64 }, { 4, 6 }, { 5, 0, 66 }, { 6, 1, 68 }, { 7, 38 }, { 8, 40 }, { 9, 4, 70 }, { 10, 10, 74 }, { 11, 5, 44, 72 }, { 12, 15 }, { 13, 7, 46 }};

//this function returns the GPIOs direction directory corresponding to the pin on which connection is made.

char* concatenate_direction(char file_path[10]){

	static char main1[100];
	sprintf(main1, "/sys/class/gpio/%s/direction", file_path);
	return main1;
	free(main1);		
}

//this function returns the GPIOs value directory corresponding to the pin on which connection is made.

char* concatenate_value(char file_path[10]){

	static char main1[100];
	sprintf(main1, "/sys/class/gpio/%s/value", file_path);
	return main1;
	free(main1);		
}

/*this function sets all levl shifters direction to out. This is hard coded to export all the level shifters because for all the GPIOs level shifters have a direction out for corresponding MUX values.*/

void level_shifter(){

	int FdExport, Fd32, Fd28, Fd34, Fd16, Fd36, Fd18, Fd20, Fd22, Fd26, Fd24, Fd42, Fd30;

	FdExport = open("/sys/class/gpio/export", O_WRONLY);
	if (FdExport < 0)
	{
		printf("gpio export open failed \n");
	}

	if(0 > write(FdExport,"32",2))
		printf("error in FdExport for level shifter 32 \n");
	if(0 > write(FdExport,"28",2))
		printf("error in FdExport for level shifter 28 \n");
	if(0 > write(FdExport,"34",2))
		printf("error in FdExport for level shifter 34 \n");
	if(0 > write(FdExport,"16",2))
		printf("error in FdExport for level shifter 16 \n");
	if(0 > write(FdExport,"36",2))
		printf("error in FdExport for level shifter 36 \n");
	if(0 > write(FdExport,"18",2))
		printf("error in FdExport for level shifter 18 \n");
	if(0 > write(FdExport,"20",2))
		printf("error in FdExport for level shifter 20 \n");
	if(0 > write(FdExport,"22",2))
		printf("error in FdExport for level shifter 22 \n");
	if(0 > write(FdExport,"26",2))
		printf("error in FdExport for level shifter 26 \n");
	if(0 > write(FdExport,"24",2))
		printf("error in FdExport for level shifter 24 \n");
	if(0 > write(FdExport,"42",2))
		printf("error in FdExport for level shifter 42 \n");
	if(0 > write(FdExport,"30",2))
		printf("error in FdExport for level shifter 30 \n");
	close(FdExport);

	Fd32 = open("/sys/class/gpio/gpio32/direction", O_WRONLY);
	if (Fd32 < 0)
	{
		printf("\n gpio32 direction open failed  \n");
	}
	Fd28 = open("/sys/class/gpio/gpio28/direction", O_WRONLY);
	if (Fd28 < 0)
	{
		printf("\n gpio28 direction open failed \n");
	}
	Fd34 = open("/sys/class/gpio/gpio34/direction", O_WRONLY);
	if (Fd34 < 0)
	{
		printf("\n gpio34 direction open failed \n");
	}
	Fd16 = open("/sys/class/gpio/gpio16/direction", O_WRONLY);
	if (Fd16 < 0)
	{
		printf("\n gpio16 direction open failed \n");
	}
	Fd36 = open("/sys/class/gpio/gpio36/direction", O_WRONLY);
	if (Fd36 < 0)
	{
		printf("\n gpio36 direction open failed \n");
	}
	Fd18 = open("/sys/class/gpio/gpio18/direction", O_WRONLY);
	if (Fd18 < 0)
	{
		printf("\n gpio18 direction open failed \n");
	}
	Fd20 = open("/sys/class/gpio/gpio20/direction", O_WRONLY);
	if (Fd20 < 0)
	{
		printf("\n gpio20 direction open failed \n");
	}
	Fd22 = open("/sys/class/gpio/gpio22/direction", O_WRONLY);
	if (Fd22 < 0)
	{
		printf("\n gpio22 direction open failed \n");
	}
	Fd26 = open("/sys/class/gpio/gpio26/direction", O_WRONLY);
	if (Fd26 < 0)
	{
		printf("\n gpio26 direction open failed \n");
	}
	Fd24 = open("/sys/class/gpio/gpio24/direction", O_WRONLY);
	if (Fd24 < 0)
	{
		printf("\n gpio24 direction open failed \n");
	}
	Fd42 = open("/sys/class/gpio/gpio42/direction", O_WRONLY);
	if (Fd42 < 0)
	{
		printf("\n gpio42 direction open failed \n");
	}
	Fd30 = open("/sys/class/gpio/gpio30/direction", O_WRONLY);
	if (Fd30 < 0)
	{
		printf("\n gpio30 direction open failed \n");
	}

	if(0 > write(Fd32,"out",3))
		printf("error Fd32 \n");
	if(0 > write(Fd28,"out",3))
		printf("error Fd28 \n");
	if(0 > write(Fd34,"out",3))
		printf("error Fd34 \n");
	if(0 > write(Fd16,"out",3))
		printf("error Fd16 \n");
	if(0 > write(Fd36,"out",3))
		printf("error Fd36 \n");
	if(0 > write(Fd18,"out",3))
		printf("error Fd18 \n");
	if(0 > write(Fd20,"out",3))
		printf("error Fd20 \n");
	if(0 > write(Fd22,"out",3))
		printf("error Fd22 \n");
	if(0 > write(Fd26,"out",3))
		printf("error Fd26 \n");
	if(0 > write(Fd24,"out",3))
		printf("error Fd24 \n");
	if(0 > write(Fd42,"out",3))
		printf("error Fd42 \n");
	if(0 > write(Fd30,"out",3))
		printf("error Fd30 \n");
}

/*this function exports corresponding GPIOs based on the input coming from main.
a1 is a char that has gpio value in string format for corresponding pin that user chooses in main, this will be used to export /sys/class/gpio 
if a pin has no mux or mux2 then a2 and a3 will be blank in which case code will skip step 2 and 3.

g1 has gpio"x", where x is the gpio value for pin which will be used to export direction for the pin.
if a pin has no mux or mux2, NULL will be received here and code will skip step 4 and 5*/

void IOSetup(char a1[4], char a2[4], char a3[3], char g1[8], char g2[8], char g3[8])
{
	int FdExport, Fd1, Fd2, Fd3;

	FdExport = open("/sys/class/gpio/export", O_WRONLY);
	if (FdExport < 0)
	{
		printf("gpio export open failed \n");
	}
	
	if(strcmp(a1,"0")!=0){
		if(0 > write(FdExport,a1,2))
			printf("error FdExport %s \n", a1);
	}
	if(strcmp(a2,"0")!=0){
		if(0 > write(FdExport,a2,2))                                 //step 2
			printf("error FdExport %s \n", a2);
	}
	if(strcmp(a3,"0")!=0){                                              //step 3
		if(0 > write(FdExport,a3,2))
			printf("error FdExport %s \n", a3);
	}
	close(FdExport);

	if(strcmp(g1, "0")!=0){
		Fd1 = open(concatenate_direction(g1), O_WRONLY);
		if (Fd1 < 0)
		{
			printf("%s direction open failed. \n", g1);
		}
		if(0 > write(Fd1,"out",3))
			printf("error Fd1 \n");
		close(Fd1);
	}

	if(strcmp(g2, "0")!=0){						  //step 4
		Fd2 = open(concatenate_direction(g2), O_WRONLY);
		if (Fd2 < 0)
		{
			printf("%s direction open failed. \n", g2);
		}
		if(0 > write(Fd2,"out",3))
			printf("error Fd2 \n");
		close(Fd2);
	}

	if(strcmp(g3, "0")!=0){						//step 5
		Fd3 = open(concatenate_direction(g3), O_WRONLY);
		if (Fd3 < 0)
		{
			printf("%s direction open failed. \n", g3);
		}
		if(0 > write(Fd3,"out",3))
			printf("error Fd3 \n");
		close(Fd3);
	}
}

void *LED_Blink(void *arg){
	
	int i;
	int Led_Green, Led_Red, Led_Blue;
	struct LEDs *mydat = arg;
	Led_Red = open(concatenate_value(mydat->red), O_WRONLY); //struct LED has red/green/blue pin's GPIO value which is sent to concatenate_value function to get the corresponding /sys/class/gpio/X/value, where X is fetched from struct
	Led_Green = open(concatenate_value(mydat->green), O_WRONLY);
	Led_Blue = open(concatenate_value(mydat->blue), O_WRONLY);	
	
	while(1){

		for(i = 0; i<25; i++){
			write(Led_Red,"1",1);
			usleep(20*1000);	
			write(Led_Red, "0", 1);
			usleep(20*1000);
		}
		sleep(1);
		for(i = 0; i<25; i++){
			write(Led_Green,"1",1);
			usleep(20*1000);
			write(Led_Green, "0", 1);
			usleep(20*1000);
		}
		sleep(1);
		for(i = 0; i<25; i++){
			write(Led_Blue,"1",1);
			usleep(20*1000);
			write(Led_Blue, "0",1);
			usleep(20*1000);
		}
		sleep(1);
		for(i = 0; i<25; i++){
			write(Led_Red,"1",1);
			write(Led_Green,"1",1);
			usleep(20*1000);
			write(Led_Red,"0",1);
			write(Led_Green,"0",1);
			usleep(20*1000);
		}
		sleep(1);
		for(i = 0; i<25; i++){
			write(Led_Red,"1",1);
			write(Led_Blue,"1",1);
			usleep(20*1000);
			write(Led_Red,"0",1);
			write(Led_Blue,"0",1);
			usleep(20*1000);
		}
		sleep(1);
		for(i = 0; i<25; i++){
			write(Led_Green,"1",1);
			write(Led_Blue,"1",1);
			usleep(20*1000);
			write(Led_Green,"0",1);
			write(Led_Blue,"0",1);
			usleep(20*1000);
		}
		sleep(1);
		for(i = 0; i<25; i++){
			write(Led_Red,"1",1);
			write(Led_Green,"1",1);
			write(Led_Blue,"1",1);
			usleep(20*1000);
			write(Led_Red,"0",1);
			write(Led_Green,"0",1);
			write(Led_Blue,"0",1);
			usleep(20*1000);
		}
		sleep(1);
	}
	return NULL;
}


int main()
{
	
	pthread_t LED;

	struct LEDs myled; //struct to store GPIOs value when they are supposed to be passed to thread for LED blinking

	int linux_gpio, mux_gpio, mux2_gpio;
	int L_Red, L_Green, L_Blue;
	int mux_Red, mux2_Red, mux_Green, mux2_Green, mux_Blue, mux2_Blue;

	level_shifter();	

	char temp_Red_linux_gpio[10];
	char temp_Red_mux_gpio[10];
	char temp_Red_mux2_gpio[10];

	char temp_Green_linux_gpio[10];
	char temp_Green_mux_gpio[10];
	char temp_Green_mux2_gpio[10];

	char temp_Blue_linux_gpio[10];
	char temp_Blue_mux_gpio[10];
	char temp_Blue_mux2_gpio[10];
	
	
	printf("Enter pin connected to Red LED: ");
    	scanf("%d", &L_Red);
	if(L_Red==0 || L_Red==4 || L_Red==7 || L_Red==8 || L_Red==12){
		
		linux_gpio = pin_data[L_Red][1]; //to get corresponding linux pin from 2D matrix (LOGIC REAMINS SAME FOR FOLLOWING CODE FOR GREEN AND BLUE LED AS WELL)
		char str_linux_gpio[7];
		sprintf(str_linux_gpio, "%d", linux_gpio); //typecasting int to string to be passed in IOsetup() (LOGIC REAMINS SAME FOR FOLLOWING CODE FOR GREEN AND BLUE LED AS WELL)
		sprintf(temp_Red_linux_gpio, "gpio%d", linux_gpio); //making pin's GPIO value as gpio'value' so that it can be used per  convinience (LOGIC REAMINS SAME FOR FOLLOWING CODE FOR GREEN AND BLUE LED AS WELL)
		IOSetup(str_linux_gpio, "0", "0", temp_Red_linux_gpio, "0", "0");
		sprintf(myled.red, "%s", temp_Red_linux_gpio); //storing gpio pin value in struct so that it can be passed to thread (LOGIC REAMINS SAME FOR FOLLOWING CODE FOR GREEN AND BLUE LED AS WELL)
	}
	else if(L_Red == 1 || L_Red==2 || L_Red==5 || L_Red==6 || L_Red==9 || L_Red==10 || L_Red==13){
		
		linux_gpio = pin_data[L_Red][1];
		mux_gpio = pin_data[L_Red][2];
		char str_linux_gpio[7], str_mux_gpio[7];
		sprintf(str_linux_gpio, "%d", linux_gpio);
		sprintf(str_mux_gpio, "%d", mux_gpio);
		sprintf(temp_Red_linux_gpio, "gpio%d", linux_gpio);
		sprintf(temp_Red_mux_gpio, "gpio%d", mux_gpio);
		IOSetup(str_linux_gpio, str_mux_gpio, "0", temp_Red_linux_gpio, temp_Red_mux_gpio, "0");
		sprintf(myled.red, "%s", temp_Red_linux_gpio);
		mux_Red = open(concatenate_value(temp_Red_mux_gpio), O_WRONLY);
		write(mux_Red,"0",1);
	}
	else if(L_Red==3 || L_Red==11){
		
		linux_gpio = pin_data[L_Red][1];
		mux_gpio = pin_data[L_Red][2];
		mux2_gpio = pin_data[L_Red][3];
		char str_linux_gpio[7], str_mux_gpio[7], str_mux2_gpio[7];
		sprintf(str_linux_gpio, "%d", linux_gpio);
		sprintf(str_mux_gpio, "%d", mux_gpio);
		sprintf(str_mux2_gpio, "%d", mux2_gpio);
		sprintf(temp_Red_linux_gpio, "gpio%d", linux_gpio);
		sprintf(temp_Red_mux_gpio, "gpio%d", mux_gpio);
		sprintf(temp_Red_mux2_gpio, "gpio%d", mux2_gpio);
		IOSetup(str_linux_gpio, str_mux_gpio, str_mux2_gpio, temp_Red_linux_gpio, temp_Red_mux_gpio, temp_Red_mux2_gpio);
		sprintf(myled.red, "%s", temp_Red_linux_gpio);
		mux_Red = open(concatenate_value(temp_Red_mux_gpio), O_WRONLY);
		write(mux_Red,"0",1);
		mux2_Red = open(concatenate_value(temp_Red_mux2_gpio), O_WRONLY);
		write(mux2_Red,"0",1);
	}

	printf("Enter pin connected to Green LED: ");
    	scanf("%d", &L_Green);
	if(L_Green==0 || L_Green==4 || L_Green==7 || L_Green==8 || L_Green==12){
		
		linux_gpio = pin_data[L_Green][1];
		char str_linux_gpio[7];
		sprintf(str_linux_gpio, "%d", linux_gpio);
		sprintf(temp_Green_linux_gpio, "gpio%d", linux_gpio);
		IOSetup(str_linux_gpio, "0", "0", temp_Green_linux_gpio, "0", "0");
		sprintf(myled.green, "%s", temp_Green_linux_gpio);
	}
	else if(L_Green == 1 || L_Green==2 || L_Green==5 || L_Green==6 || L_Green==9 || L_Green==10 || L_Green==13){
		
		linux_gpio = pin_data[L_Green][1];
		mux_gpio = pin_data[L_Green][2];
		char str_linux_gpio[7], str_mux_gpio[7];
		sprintf(str_linux_gpio, "%d", linux_gpio);
		sprintf(str_mux_gpio, "%d", mux_gpio);
		sprintf(temp_Green_linux_gpio, "gpio%d", linux_gpio);
		sprintf(temp_Green_mux_gpio, "gpio%d", mux_gpio);
		IOSetup(str_linux_gpio, str_mux_gpio, "0", temp_Green_linux_gpio, temp_Green_mux_gpio, "0");
		sprintf(myled.green, "%s", temp_Green_linux_gpio);
		mux_Green = open(concatenate_value(temp_Green_mux_gpio), O_WRONLY);
		write(mux_Green,"0",1);
	}
	else if(L_Green==3 || L_Green==11){
		
		linux_gpio = pin_data[L_Green][1];
		mux_gpio = pin_data[L_Green][2];
		mux2_gpio = pin_data[L_Green][3];
		char str_linux_gpio[7], str_mux_gpio[7], str_mux2_gpio[7];
		sprintf(str_linux_gpio, "%d", linux_gpio);
		sprintf(str_mux_gpio, "%d", mux_gpio);
		sprintf(str_mux2_gpio, "%d", mux2_gpio);
		sprintf(temp_Green_linux_gpio, "gpio%d", linux_gpio);
		sprintf(temp_Green_mux_gpio, "gpio%d", mux_gpio);
		sprintf(temp_Green_mux2_gpio, "gpio%d", mux2_gpio);
		IOSetup(str_linux_gpio, str_mux_gpio, str_mux2_gpio, temp_Green_linux_gpio, temp_Green_mux_gpio, temp_Green_mux2_gpio);
		sprintf(myled.green, "%s", temp_Green_linux_gpio);
		mux_Green = open(concatenate_value(temp_Green_mux_gpio), O_WRONLY);
		write(mux_Green,"0",1);
		mux2_Green = open(concatenate_value(temp_Green_mux2_gpio), O_WRONLY);
		write(mux2_Green,"0",1);
	}

        printf("Enter pin connected to Blue LED: ");
    	scanf("%d", &L_Blue);
	if(L_Blue==0 || L_Blue==4 || L_Blue==7 || L_Blue==8 || L_Blue==12){
		
		linux_gpio = pin_data[L_Blue][1];
		char str_linux_gpio[7];
		sprintf(str_linux_gpio, "%d", linux_gpio);
		sprintf(temp_Blue_linux_gpio, "gpio%d", linux_gpio);
		IOSetup(str_linux_gpio, "0", "0", temp_Blue_linux_gpio, "0", "0");
		sprintf(myled.blue, "%s", temp_Blue_linux_gpio);
	}
	else if(L_Blue == 1 || L_Blue==2 || L_Blue==5 || L_Blue==6 || L_Blue==9 || L_Blue==10 || L_Blue==13){
		
		linux_gpio = pin_data[L_Blue][1];
		mux_gpio = pin_data[L_Blue][2];
		char str_linux_gpio[7], str_mux_gpio[7];
		sprintf(str_linux_gpio, "%d", linux_gpio);
		sprintf(str_mux_gpio, "%d", mux_gpio);
		sprintf(temp_Blue_linux_gpio, "gpio%d", linux_gpio);
		sprintf(temp_Blue_mux_gpio, "gpio%d", mux_gpio);
		IOSetup(str_linux_gpio, str_mux_gpio, "0", temp_Blue_linux_gpio, temp_Blue_mux_gpio, "0");
		sprintf(myled.blue, "%s", temp_Blue_linux_gpio);
		mux_Blue = open(concatenate_value(temp_Blue_mux_gpio), O_WRONLY);
		write(mux_Blue,"0",1);
	}
	else if(L_Blue==3 || L_Blue==11){
		
		linux_gpio = pin_data[L_Blue][1];
		mux_gpio = pin_data[L_Blue][2];
		mux2_gpio = pin_data[L_Blue][3];
		char str_linux_gpio[7], str_mux_gpio[7], str_mux2_gpio[7];
		sprintf(str_linux_gpio, "%d", linux_gpio);
		sprintf(str_mux_gpio, "%d", mux_gpio);
		sprintf(str_mux2_gpio, "%d", mux2_gpio);
		sprintf(temp_Blue_linux_gpio, "gpio%d", linux_gpio);
		sprintf(temp_Blue_mux_gpio, "gpio%d", mux_gpio);
		sprintf(temp_Blue_mux2_gpio, "gpio%d", mux2_gpio);
		IOSetup(str_linux_gpio, str_mux_gpio, str_mux2_gpio, temp_Blue_linux_gpio, temp_Blue_mux_gpio, temp_Blue_mux2_gpio);
		sprintf(myled.blue, "%s", temp_Blue_linux_gpio);
		mux_Blue = open(concatenate_value(temp_Blue_mux_gpio), O_WRONLY);
		write(mux_Blue,"0",1);
		mux2_Blue = open(concatenate_value(temp_Blue_mux2_gpio), O_WRONLY);
		write(mux2_Blue,"0",1);
	}

/*code to handle mouse event. Please use mouse left click as your event to restart sequence from R, G, B, R&G, R&B, 
G&B, R&G&B. Thread is used to start the sequence and killed and restarted again upon mouse click to ensure restarting sequence*/

	int fd, bytes;
	unsigned char data[3];
	fd = open(MOUSE_DEV, O_RDWR);
	if(fd == -1)
	{
		printf("ERROR Opening %s \n", MOUSE_DEV);
		return -1;
	}

	int left;	
	
	pthread_create (&LED,NULL,LED_Blink,(void *)&myled);

	while(1)
	{    
		bytes = read(fd, data, sizeof(data));
		if(bytes > 0)
		{
			left = data[0] & 0x1;

			if(left==1){
				pthread_cancel(LED);
				pthread_create (&LED,NULL,LED_Blink,(void *)&myled);
						
			}		
		}
	}

	close(fd);
	pthread_join(LED,NULL);
	return 0;
}
