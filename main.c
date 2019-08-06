/*
 * MicroChariot.c
 *
 * Created: 7/3/2019 11:23:21 AM
 * Author : drew
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	//output pin mapping
	/*
		PE3 = OC3A
		PE4 = OC3B
		PE5 = OC3C
	//----------------------------------------------------------
		PB5 = OC1A
		PB6 = OC1B
		PB7 = OC1C
	*/
	
	// 0xFF sets all pins to output, technically only need 3
		DDRE |= 0xFF;
	//----------------------------------------------------------
		DDRB |= 0xFF;
	
	//set up waveform generation mode (fast PWM)
		TCCR3A |= 1<<WGM31;
		TCCR3B |= 1<<WGM33 | 1<<WGM32;
	//----------------------------------------------------------
		TCCR1A |= 1<<WGM11;
		TCCR1B |= 1<<WGM13 | 1<<WGM12;
	
	//set up clock prescaler
		TCCR3B |= 1<<CS30;
	//----------------------------------------------------------
		TCCR1B |= 1<<CS10;
	
	//need to set COMnx0 and COMnx1 of whichever output port is in use
		TCCR3A |= 1<<COM3A1 | 1<<COM3A0;
		TCCR3A |= 1<<COM3B1 | 1<<COM3B0;
		TCCR3A |= 1<<COM3C1 | 1<<COM3C0;
	//----------------------------------------------------------
		TCCR1A |= 1<<COM1A1 | 1<<COM1A0;
		TCCR1A |= 1<<COM1B1 | 1<<COM1B0;
		TCCR1A |= 1<<COM1C1 | 1<<COM1C0;
	
	//set ICRx (top) to 19999 (20ms or 50Hz)
		ICR3 = 19999;
	//----------------------------------------------------------
		ICR1 = 19999;
	
	//----------------------------------------------------------
	//DONE WITH SET UP
	//FUNCTIONS THAT SET MOTOR LEVELS
	//----------------------------------------------------------
	
	float midpoint = 1450;
	float halfRange = 500;
	
	void setMotorE3(float spd) {
		OCR1A = ICR1 - (midpoint + (halfRange * spd));
	}
	void setMotorE4(float spd) {
		OCR1B = ICR1 - (midpoint + (halfRange * spd));
	}
	void setMotorE5(float spd) {
		OCR1C = ICR1 - (midpoint + (halfRange * spd));
	}
	void setMotorB5(float spd) {
		OCR3A = ICR3 - (midpoint + (halfRange * spd));
	}
	void setMotorB6(float spd) {
		OCR3B = ICR3 - (midpoint + (halfRange * spd));
	}
	void setMotorB7(float spd) {
		OCR3C = ICR3 - (midpoint + (halfRange * spd));
	}
	
	//this is an example, don't know what ports go where yet
	void setLeftMotors(float spd) {
		setMotorB5(spd);
		setMotorB6(spd);
	}
	
	//----------------------------------------------------------
	//BUTTON CODE
	//----------------------------------------------------------
	
	int buttonZero = 0;
	int buttonOne = 0;
	int buttonTwo = 0;
	int buttonThree = 0;
	int buttonFour = 0;
	int buttonFive = 0;
	int buttonSix = 0;
	int buttonSeven = 0;
	
	void checkButtons()
	{
		if(!(PIND & 0x01)){
			buttonZero = 1;
		}else{
			buttonZero = 0;
		}if(!(PIND & 0x02)){
			buttonOne = 1;
		}else{
			buttonOne = 0;
		}if(!(PIND & 0x04)){
			buttonTwo = 1;
		}else{
			buttonTwo = 0;
		}if(!(PIND & 0x08)){
			buttonThree = 1;
		}else{
			buttonThree = 0;
		}if(!(PIND & 0x10)){
			buttonFour = 1;
		}else{
			buttonFour = 0;
		}if(!(PIND & 0x20)){
			buttonFive = 1;
		}else{
			buttonFive = 0;
		}if(!(PIND & 0x40)){
			buttonSix = 1;
		}else{
			buttonSix = 0;
		}if(!(PIND & 0x80)){
			buttonSeven = 1;
		}else{
			buttonSeven = 0;
		}
	}
	
	while(1) {
		//main loop to do stuff
		
		//always call checkButtons() to read new button values
		checkButtons();
		
		if (buttonOne == 1)
		{
			setLeftMotors(0.5);
		}
	}
}