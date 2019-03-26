
/*****This code performs RGB display using PWM implementation. The PWMs being implemented are pwm1, pwm9 and pwm7******/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <linux/input.h>
#include <pthread.h>
#define MOUSEFILE "/dev/input/mice"
#define PWM_PERIOD 1000000

int pwm1,pwm2,LED1,LED2,LED3,pwm,pwm3;
int PWMExport, pwm123, duty;
int period;
char buffer[100];
char buffer1[256],buffer2[100];

void IOSetup(void){
	
	int FdExport;
	FdExport = open("/sys/class/gpio/export", O_WRONLY);
	if (FdExport < 0)
	{
   	 	printf("\n gpio export open failed");
	}

/**********IOPin Initialisations************/

//IO PIN 3
	if(0<write(FdExport, "16",2))
   		 printf("error FdExport 16");
	if(0<write(FdExport, "17",2))
    		printf("error FdExport 17");
	if(0<write(FdExport, "76",2))
    		printf("error FdExport 16");
	if(0<write(FdExport, "64",2))
    		printf("error FdExport 17"); 


//IO PIN 11
	if(0<write(FdExport, "24",2))
    		printf("error FdExport 24");
	if(0<write(FdExport, "25",2))
   		 printf("error FdExport 25");
	if(0<write(FdExport, "44",2))
   		 printf("error FdExport 44");
	if(0<write(FdExport, "72",2))
    		printf("error FdExport 72"); 


//IO PIN 9
	if(0<write(FdExport, "22",2))
    		printf("error FdExport 18");
	if(0<write(FdExport, "23",2))
    		printf("error FdExport 19");
	if(0<write(FdExport, "70",2))
    		printf("error FdExport 66"); 


	close(FdExport);


//IO PIN 3

	pwm1 = open("/sys/class/gpio/gpio16/direction", O_WRONLY);
	if(0< write(pwm1,"out",3))
    		printf("error gpio16");
	close(pwm1);

	pwm1 = open("/sys/class/gpio/gpio17/direction", O_WRONLY);
	if(0< write(pwm1,"in",2))
    		printf("error gpio17");
	close(pwm1);

	pwm1 = open("/sys/class/gpio/gpio76/direction", O_WRONLY);
	if(0< write(pwm1,"out",3))
    		printf("error gpio76");
	close(pwm1);

	pwm1 = open("/sys/class/gpio/gpio64/direction", O_WRONLY);
	if(0< write(pwm1,"out",3))
    		printf("error gpio64");
	close(pwm1);


	pwm1 = open("/sys/class/gpio/gpio16/value", O_WRONLY);
	write(pwm1,"0",1);
	close(pwm1);

	pwm1 =open("/sys/class/gpio/gpio76/value", O_WRONLY);
	write(pwm1,"0",1);
	close(pwm);

	pwm1 =open("/sys/class/gpio/gpio64/value", O_WRONLY);
	write(pwm1,"1",1);
	close(pwm1); 

//IO PIN 11

	pwm2 = open("/sys/class/gpio/gpio24/direction", O_WRONLY);
	if(0< write(pwm2,"out",3))
    		printf("error gpio24");
	close(pwm2);

	pwm2 = open("/sys/class/gpio/gpio25/direction", O_WRONLY);
	if(0< write(pwm2,"in",3))
    		printf("error gpio25");
	close(pwm2);

	pwm2 = open("/sys/class/gpio/gpio44/direction", O_WRONLY);
	if(0< write(pwm2,"out",3))
		printf("error gpio44");
	close(pwm2);

	pwm2 = open("/sys/class/gpio/gpio72/direction", O_WRONLY);
	if(0< write(pwm2,"out",3))
    		printf("error gpio72");
	close(pwm2);


	pwm2 = open("/sys/class/gpio/gpio24/value", O_WRONLY);
	write(pwm2,"0",1);
	close(pwm2);
	pwm2 =open("/sys/class/gpio/gpio44/value", O_WRONLY);
	write(pwm2,"0",1);
	close(pwm2);
	pwm2 =open("/sys/class/gpio/gpio72/value", O_WRONLY);
	write(pwm2,"1",1);
	close(pwm2); 


//IO PIN 9

	pwm3 = open("/sys/class/gpio/gpio22/direction", O_WRONLY);
	if(0< write(pwm3,"out",3))
    		printf("error gpio22");
	close(pwm3);

	pwm3 = open("/sys/class/gpio/gpio23/direction", O_WRONLY);
	if(0< write(pwm3,"out",3))
		 printf("error gpio23");
	close(pwm3); 

	pwm3 = open("/sys/class/gpio/gpio23/value", O_WRONLY);
	write(pwm3,"0",1);
	close(pwm3); 

	pwm3 =open("/sys/class/gpio/gpio70/value", O_WRONLY);
	write(pwm3,"1",1);
	close(pwm3); 

}

/*****This function initialises the PWM number, period and duty cycle******/

/****PERIOD = 40ms***/

/****DUTY CYCLE = 20ms***/

void PWM_init()
{
	char buffer1[256];

	IOSetup();

	PWMExport = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);

	if (PWMExport < 0)
	{
    		printf("\n gpio export open failed");
	}

	if(0<write(PWMExport, "1",1))
    	printf("error ");

	if(0<write(PWMExport, "9",1))
    	printf("error ");

	if(0<write(PWMExport, "7",1))
    	printf("error ");

	close(PWMExport);

	period = 80000000;
	duty =  period/2; 
	pwm2 = open("/sys/class/pwm/pwmchip0/device/pwm_period", O_WRONLY);
	sprintf(buffer1, "%d",period);
	write(pwm2,buffer1,strlen(buffer1));
	close(pwm2); 

}

/****To make the RED LED blink****/
void PWM_Red()
{
	pwm2 = open("/sys/class/pwm/pwmchip0/pwm9/enable", O_WRONLY);
	sprintf(buffer2, "%d", 1);
	write(pwm2, buffer2, strlen(buffer2));
	close(pwm2); 

	pwm2 = open("/sys/class/pwm/pwmchip0/pwm9/duty_cycle", O_WRONLY);
	sprintf(buffer, "%d", duty);
	write(pwm2, buffer, strlen(buffer)); 
	close(pwm2);
 
	pwm2 = open("/sys/class/pwm/pwmchip0/pwm9/enable", O_WRONLY);
	sprintf(buffer2, "%d", 0);
	write(pwm2, buffer2, strlen(buffer2));
	close(pwm2);

}

/****To make the GREEN LED blink****/
void PWM_Green()
{
	pwm3 = open("/sys/class/pwm/pwmchip0/pwm7/enable", O_WRONLY);
	sprintf(buffer2, "%d", 1);
	write(pwm3, buffer2, strlen(buffer2));
	close(pwm3); 

	pwm3 = open("/sys/class/pwm/pwmchip0/pwm7/duty_cycle", O_WRONLY);
	sprintf(buffer, "%d", duty);
	write(pwm3, buffer, strlen(buffer));
	close(pwm3); 

	pwm3 = open("/sys/class/pwm/pwmchip0/pwm7/enable", O_WRONLY);
	sprintf(buffer2, "%d", 0);
	write(pwm3, buffer2, strlen(buffer2));
	close(pwm3); 

}

/****To make the BLUE LED blink****/
void PWM_Blue()
{
	pwm1 = open("/sys/class/pwm/pwmchip0/pwm1/enable", O_WRONLY);
	sprintf(buffer2, "%d", 1);
	write(pwm1, buffer2, strlen(buffer2));
	close(pwm1);

	pwm1 = open("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", O_WRONLY);
	sprintf(buffer, "%d", duty);
	write(pwm1, buffer, strlen(buffer));
	close(pwm1); 

	pwm1 = open("/sys/class/pwm/pwmchip0/pwm1/enable", O_WRONLY);
	sprintf(buffer2, "%d", 0);
	write(pwm1, buffer2, strlen(buffer2));
	close(pwm1);

}


/****To make the REDBLUE LEDs blink****/
void PWM_RedBlue()
{
	pwm1 = open("/sys/class/pwm/pwmchip0/pwm1/enable", O_WRONLY);
	sprintf(buffer2, "%d", 1);
	write(pwm1, buffer2, strlen(buffer2));
	close(pwm1);

	pwm2 = open("/sys/class/pwm/pwmchip0/pwm9/enable", O_WRONLY);
	sprintf(buffer2, "%d", 1);
	write(pwm2, buffer2, strlen(buffer2));
	close(pwm2); 

	pwm1 = open("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", O_WRONLY);
	sprintf(buffer, "%d", duty);
	write(pwm1, buffer, strlen(buffer));
	close(pwm1);

	pwm2 = open("/sys/class/pwm/pwmchip0/pwm9/duty_cycle", O_WRONLY);
	sprintf(buffer, "%d", duty);
	write(pwm2, buffer, strlen(buffer)); 
	close(pwm2);

	pwm1 = open("/sys/class/pwm/pwmchip0/pwm1/enable", O_WRONLY);
	sprintf(buffer2, "%d", 0);
	write(pwm1, buffer2, strlen(buffer2));
	close(pwm1);

	pwm2 = open("/sys/class/pwm/pwmchip0/pwm9/enable", O_WRONLY);
	sprintf(buffer2, "%d", 0);
	write(pwm2, buffer2, strlen(buffer2));
	close(pwm2); 

}

/****To make the REDGREEN LEDs blink****/
void PWM_RedGreen()
{
	pwm2 = open("/sys/class/pwm/pwmchip0/pwm9/enable", O_WRONLY);
	sprintf(buffer2, "%d", 1);
	write(pwm2, buffer2, strlen(buffer2));
	close(pwm2); 
	
	pwm3 = open("/sys/class/pwm/pwmchip0/pwm7/enable", O_WRONLY);
	sprintf(buffer2, "%d", 1);
	write(pwm3, buffer2, strlen(buffer2));
	close(pwm3); 

	pwm3 = open("/sys/class/pwm/pwmchip0/pwm7/duty_cycle", O_WRONLY);
	sprintf(buffer, "%d", duty);
	write(pwm3, buffer, strlen(buffer));
	close(pwm3); 

	pwm2 = open("/sys/class/pwm/pwmchip0/pwm9/duty_cycle", O_WRONLY);
	sprintf(buffer, "%d", duty);
	write(pwm2, buffer, strlen(buffer)); 
	close(pwm2);

	pwm3 = open("/sys/class/pwm/pwmchip0/pwm7/enable", O_WRONLY);
	sprintf(buffer2, "%d", 0);
	write(pwm3, buffer2, strlen(buffer2));
	close(pwm3); 

	pwm2 = open("/sys/class/pwm/pwmchip0/pwm9/enable", O_WRONLY);
	sprintf(buffer2, "%d", 0);
	write(pwm2, buffer2, strlen(buffer2));
	close(pwm2); 

}

/****To make the BLUEGREEN LEDs blink****/
void PWM_BlueGreen()
{
	pwm3 = open("/sys/class/pwm/pwmchip0/pwm7/enable", O_WRONLY);
	sprintf(buffer2, "%d", 1);
	write(pwm3, buffer2, strlen(buffer2));
	close(pwm3); 

	pwm1 = open("/sys/class/pwm/pwmchip0/pwm1/enable", O_WRONLY);
	sprintf(buffer2, "%d", 1);
	write(pwm1, buffer2, strlen(buffer2));
	close(pwm1);

	pwm1 = open("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", O_WRONLY);
	sprintf(buffer, "%d", duty);
	write(pwm1, buffer, strlen(buffer));
	close(pwm1); 

	pwm3 = open("/sys/class/pwm/pwmchip0/pwm7/duty_cycle", O_WRONLY);
	sprintf(buffer, "%d", duty);
	write(pwm3, buffer, strlen(buffer));
	close(pwm3);

	pwm1 = open("/sys/class/pwm/pwmchip0/pwm1/enable", O_WRONLY);
	sprintf(buffer2, "%d", 0);
	write(pwm1, buffer2, strlen(buffer2));
	close(pwm1);

	pwm3 = open("/sys/class/pwm/pwmchip0/pwm7/enable", O_WRONLY);
	sprintf(buffer2, "%d", 0);
	write(pwm3, buffer2, strlen(buffer2));
	close(pwm3); 

}

/****To make the REDGREENBLUE LEDs blink****/
void PWM_RGB()
{
	pwm1 = open("/sys/class/pwm/pwmchip0/pwm1/enable", O_WRONLY);
	sprintf(buffer2, "%d", 1);
	write(pwm1, buffer2, strlen(buffer2));
	close(pwm1);

	pwm3 = open("/sys/class/pwm/pwmchip0/pwm7/enable", O_WRONLY);
	sprintf(buffer2, "%d", 1);
	write(pwm3, buffer2, strlen(buffer2));
	close(pwm3); 

	pwm2 = open("/sys/class/pwm/pwmchip0/pwm9/enable", O_WRONLY);
	sprintf(buffer2, "%d", 1);
	write(pwm2, buffer2, strlen(buffer2));
	close(pwm2);

	pwm3 = open("/sys/class/pwm/pwmchip0/pwm7/duty_cycle", O_WRONLY);
	sprintf(buffer, "%d", duty);
	write(pwm3, buffer, strlen(buffer));
	close(pwm3);

	pwm1 = open("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", O_WRONLY);
	sprintf(buffer, "%d", duty);
	write(pwm1, buffer, strlen(buffer));
	close(pwm1); 

	pwm2 = open("/sys/class/pwm/pwmchip0/pwm9/duty_cycle", O_WRONLY);
	sprintf(buffer, "%d", duty);
	write(pwm2, buffer, strlen(buffer)); 
	close(pwm2);

	pwm1 = open("/sys/class/pwm/pwmchip0/pwm1/enable", O_WRONLY);
	sprintf(buffer2, "%d", 0);
	write(pwm1, buffer2, strlen(buffer2));
	close(pwm1);

	pwm3 = open("/sys/class/pwm/pwmchip0/pwm7/enable", O_WRONLY);
	sprintf(buffer2, "%d", 0);
	write(pwm3, buffer2, strlen(buffer2));
	close(pwm3); 

	pwm2 = open("/sys/class/pwm/pwmchip0/pwm9/enable", O_WRONLY);
	sprintf(buffer2, "%d", 0);
	write(pwm2, buffer2, strlen(buffer2));
	close(pwm2);

}       


/****Thread that implements all the LEDs in thr given order****/
void *LED_PWM(void *arg){
		
	int i;
while(1){
	for(i=0; i<25; i++){
		PWM_Red();
	}
	for(i=0; i<25; i++){
		PWM_Green();
	}
	for(i=0; i<25; i++){
		PWM_Blue();
	}
	for(i=0; i<25; i++){
		PWM_RedGreen();
	}
	for(i=0; i<25; i++){	
		PWM_RedBlue();
	}
	for(i=0; i<25; i++){
		PWM_BlueGreen();
	}
	for(i=0; i<25; i++){
		PWM_RGB();
	}
}
return NULL;

}


int main()
{
	
	pthread_t LED;	
	int fd, bytes,left=0;
	unsigned char data[3];
	fd = open(MOUSEFILE, O_RDWR);
	printf("I m in!");
	IOSetup();
	PWM_init();
	pthread_create(&LED, NULL, &LED_PWM, NULL);
	if(fd == -1)
	{
		printf("ERROR Opening %s\n", MOUSEFILE);
		return -1;
	}
	while(1){
		bytes = read(fd, data, sizeof(data)); /****Everytime left click happens, duty cycle decrements to 90 percent of its original value****/
		if(bytes > 0)
		{
			left = data[0] & 0x1;

			if(left==1){				
				if (duty > 0)
					duty = 0.9 * duty;
				printf("DUTY %d \n", duty);						
			}		
		}
	}
	close(fd);
   	printf("\nIt Worked! \n");
	return 0;
}


/**********End Of Code***********/

