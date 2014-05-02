#include <Wire.h>

class Gyroscope{
	//Tris10 TrackMotion
	int address;
	public:
		Gyroscope(int i2cAddress){ address=i2cAddress; }
		void init(){
			Wire.beginTransmission(address);
			//Wire.write(0x00);
			//Configuration registers for gyro go here
			Wire.endTransmission();
		}
		int read(){
			int returnVal;
			Wire.beginTransmission(address);

			Wire.endTransmission();

			//Assuming from previous experience that value is 2 byte
			Wire.requestFrom(address, 2);
			while(Wire.available() < 2);
			returnVal=Wire.read() <<8;
			returnVal |= Wire.read();
		}
};

class Magnetometer{
	int address;
	int threshold;
	public:
		Magnetometer(int i2cAddress, int mineThreshold){
			threshold=mineThreshold;
			address=i2cAddress;
		}

		void init(){
			//Writes to registers for setup;

			Wire.beginTransmission(address);
			//Continuous mode
			Wire.send(0x02);
			Wire.send(0x00);
			Wire.endTransmission();

			Wire.beginTransmission(address);
			//ODR=30Hz, 4 samples averaged per outpu
			Wire.send(0x00);
			Wire.send(0x34);
			Wire.endTransmission();
		}

		int read(){
			int val=0;
			Wire.beginTransmission(address);
			Wire.send(0x03); //x=3, y=5, z=7
			Wire.endTransmission();
			Wire.requestFrom(address, 2);
			while (Wire.available() < 2);
			val = Wire.receive()<<8; //msb
			val |= Wire.receive(); //lsb
			return val;
		}

		int binRead(){return (read > threshold ? 1 : 0);}
};

class IRSensor{
	//
};

class Motor{

};

class MarkerSystem{

};

class Drive{
	Gyroscope gyro;
	Motor leftMotor;
	Motor rightMotor;
	//
}