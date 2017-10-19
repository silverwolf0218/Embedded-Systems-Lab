#include <Wire.h>
#define SLAVE_ADDRESS 0x04
int number=0;
int state=0;

void setup(){
	pinMode(2,OUTPUT);
	Serial.begin(9600);
	Wire.begin(SLAVE_ADDRESS);
	Wire.onReceive(receiveData);
	Wire.onRequest(sendData);
	Serial,println("Ready!");
}

void loop(){
	delay(100);
}

void receiveData(int byteCount){
	while(Wire.available()){
		number=Wire.read();
		Serial.print("data received: ");
		Serial.println(number);
	}

	if(state==0){
		digitalWrite(2,HIGH);
		state=1;
	}
	else{
		digitalWrite(2,HIGH);
		state=0;
	}
}

void sendData(){
	Wire.write(number+1);
}