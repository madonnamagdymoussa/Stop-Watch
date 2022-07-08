
#include <stdio.h>
#include <stdlib.h> // header file for exit function
/****************************************************************************************************/
/*                                   enumeration                                                   */
/**************************************************************************************************/

enum vechile_state{
	TurnON = 1 ,  TurnOFF,  Quit
};
enum vechile_state state = TurnOFF;   // initialize the variable state with a  value off at the beginning then ask the user if he want to turn it on or off


enum Func_Options{
	OPTIONA = 0 , OPTIONB , OPTIONC , OPTIOND
};
enum Func_Options option;

typedef enum{

	OFF=0,
	ON=1
}bool;

bool AC=OFF; //create a variable related to the state of the air conditioner of type bool
               // initialize the value of AC with OFF value until there is a condition to change the value of the AC to true

bool ENGINE_CONTROLLER =OFF; //create a variable related to the state of the engine temperature controller of type bool
// initialize the value of the engine temperature controller with OFF value until there is a condition to change the value of that to true

/****************************************************************************************************/
/*                                  Prototypes                                                     */
/**************************************************************************************************/
void Ask_the_user(void);
void Sensor_set_menu(void);

void Quit_Program(void);
void (*ptr_Quit) (void);

void turnoff_Program (void);
void (*ptr_OFF) (void);

void turnon_Program (void);
void (*ptr_ON)(void);

void set_color (void);                     //option B (if option B is chosen set_color function will be called)
void set_RoomTemp(void);                  //option C (if option C  is chosen  set_RoomTemp  function will be called)
void set_EngineTemp(void);               //option D (if option D   is chosen  set_EngineTemp function will be called)
void (*arr_option[4])(void);            // array of pointers to the above functions (setting speed, setting AC,...)

void current_value(void);             // prints the current value  of the room temp, engine temp, speed, ..........

/****************************************************************************************************/
/*                                  Function definition                                            */
/**************************************************************************************************/

void Ask_the_user(void){
	printf("if you want to turn on the vechile   press 1 \n");
	printf("if you want to turn off the vechile  press 2  \n");
	printf("if you want to quit the program      press 3   \n");

}

void Sensor_set_menu(void){

	printf("optionA -> Turn off the engine         press 0 \n");
	printf("optionB -> set the traffic light color press 1  \n");
	printf("optionC -> set the room temperature    press 2   \n");
	printf("optionD -> set the engine temperature  press 3    \n");
	printf("\n");
	}


int speed;
void set_color (void){

	char color;
	printf("Enter the traffic light data \n");
	scanf(" %c",&color);

   if ('G' == color){
           speed = 100;
   }

   else if ('O' == color){
	       speed = 30;
   }

   else if('R' == color) {
	       speed = 0;
   }

   printf("The speed is %d \n", speed);
}



int room_temperature;
void set_RoomTemp(void){

	printf("Enter the temperature value \n");
		scanf("%d", &room_temperature );

		if(room_temperature < 10){
            AC = ON;
            room_temperature=20;
		}

		else if(room_temperature > 30){
		    AC = ON;
		    room_temperature=20;
		}
		else
		   AC = OFF;
	printf("The room temperature value %d\n",room_temperature);
}



int engine_temperature;
void set_EngineTemp(void){

	printf("Enter the engine temperature \n");
			scanf("%d", &engine_temperature );

     if( (engine_temperature < 100) || (engine_temperature > 150) ){
    	 ENGINE_CONTROLLER  = ON;
    	 engine_temperature = 125;
     }

     else
    	 ENGINE_CONTROLLER  = OFF;
     printf("The engine temperature value %d\n",engine_temperature);
}



void check_speed(void){  // the function checks if the speed is equal to 30 in order to do some actions

	if (30 == speed){    // two if conditions Not if else if because the two conditions might be true -> Engine controller and AC is off , so the two actions must be executed
		if (OFF == AC){
			AC=ON;
			room_temperature = room_temperature * (5/4) + 1;
		}

		if (OFF == ENGINE_CONTROLLER){
			ENGINE_CONTROLLER=ON;
			engine_temperature = engine_temperature * (5/4) + 1;
		}
	} //end of the first if
}    // end of function




void (*arr_option[4])(void)={Ask_the_user, set_color, set_RoomTemp, set_EngineTemp};
 // initialize the array of pointers to function



void Quit_Program(void){
		exit(1);
}
void (*ptr_Quit) (void)= Quit_Program; // the pointer ptr_Quit points to the Quit_Program function



 void turnoff_Program(void){
	 	 //Ask_the_user();
 }
 void (*ptr_OFF) (void)= turnoff_Program; // the pointer ptr_OFF points to the turnoff_Program function



void turnon_Program (void){

	Sensor_set_menu();


	scanf("%u", &option);
	(*arr_option[option])();   // the function will be called through the array of pointer to function
	                          //  (example: arr_option[OPTIONA],  arr_option[OPTIONB] , arr_option[OPTIONC])
	                         //   (example: arr_option[0],         arr_option[1],       arr_option[2]
	check_speed();
	printf("\n");
	current_value();
 }
void (*ptr_ON)(void)= turnon_Program; // the pointer ptr_ON points to the turnon_Program function


void current_value(void){

	printf("The current Engine state is %d\n", state);
	printf("The current Air conditioner state is %d\n", AC);
    printf("The current vehicle speed is %d\n", speed);
    printf("The current Room temperature is %d\n", room_temperature);
    printf("The current engine state is %d\n", ENGINE_CONTROLLER);
    printf("The current engine temperature is %d\n", engine_temperature );
    printf("\n");

}

int main(){

	setvbuf(stdout, NULL, _IONBF, 0);

	setvbuf(stderr, NULL, _IONBF, 0);

   while(1){


	Ask_the_user();
	  scanf("%u", &state);

	switch(state){

	case TurnON:
		printf("The vehicle engine is on \n");
		(*ptr_ON)();
		 break;

	case TurnOFF:
		printf("The vehicle engine is off \n");
		(*ptr_OFF)();
		break;

	case Quit:
		printf("Exit the program\n");
		(*ptr_Quit)();
		break;
	}


   }
}



