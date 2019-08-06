/*
 * MicroChariot.c
 *
 * Created: 7/3/2019 11:23:21 AM
 * Author : drew
 */ 

#define F_CPU 16000000
#define BUTTON_PIN PINA
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
	
	void setRightMotors(float spd) {
		setMotorE3(spd);
		setMotorE4(spd);
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
		if(!(BUTTON_PIN & 0x01)){
			buttonZero = 1;
		}else{
			buttonZero = 0;
		}if(!(BUTTON_PIN & 0x02)){
			buttonOne = 1;
		}else{
			buttonOne = 0;
		}if(!(BUTTON_PIN & 0x04)){
			buttonTwo = 1;
		}else{
			buttonTwo = 0;
		}if(!(BUTTON_PIN & 0x08)){
			buttonThree = 1;
		}else{
			buttonThree = 0;
		}if(!(BUTTON_PIN & 0x10)){
			buttonFour = 1;
		}else{
			buttonFour = 0;
		}if(!(BUTTON_PIN & 0x20)){
			buttonFive = 1;
		}else{
			buttonFive = 0;
		}if(!(BUTTON_PIN & 0x40)){
			buttonSix = 1;
		}else{
			buttonSix = 0;
		}if(!(BUTTON_PIN & 0x80)){
			buttonSeven = 1;
		}else{
			buttonSeven = 0;
		}
	}
	
	int counter = 2;
	float speeds[6] = {-0.4, -0.2, 0.0, 0.2, 0.3, 0.4};
	int speedUpState = 0;
	int speedUpLastState = 0;
	int speedDownState = 0;
	int speedDownLastState = 0;
	//increment or decrement counter that chooses motor speeds
	void updateCounter() {
		if (speedUpState == 1 && speedUpLastState == 0) {
			//up toggle button was just pushed, increment speed counter
			counter++;
		}
		if (speedDownState == 1 && speedDownLastState == 0) {
			//down toggle button was just pushed, decrement speed counter
			counter--;
		}
		if (counter > 5) {
			counter = 5;
		}
		if (counter < 0) {
			counter = 0;
		}
		
		speedUpLastState = speedUpState;
		speedDownLastState = speedDownState;
	}
	
	int count = 0;
	
	while(1) {
		//main loop to do stuff
		
		//always call checkButtons() to read new button values
		/*
		checkButtons();
		if (buttonZero == 1)
		{
			speedDownState = 1;
		}
		if (buttonOne == 1)
		{
			speedUpState = 1;
		}
		updateCounter();
		setLeftMotors(speeds[counter]*buttonTwo);
		setRightMotors(speeds[counter]*buttonThree);
		*/
		
		checkButtons();
		
		if (buttonFour == 1)
		{
			setLeftMotors(1.0);
			setRightMotors(1.0);
		}else
		{
			setLeftMotors(-1.0);
			setRightMotors(-1.0);
		}
		
		/*
		count += 1;
		
		if (count <= 100)
		{
			setRightMotors(0.5);
			setLeftMotors(0.5);
		}else if (count > 100 && count <= 200)
		{
			setRightMotors(0.0);
			setLeftMotors(0.0);
		}else if (count > 200 && count <= 300)
		{
			setRightMotors(-0.5);
			setLeftMotors(-0.5);
		}else if (count > 300 && count <= 400)
		{
			setRightMotors(0.0);
			setLeftMotors(0.0);
		}else{
			count = 0;
		}
		*/
	}
}