// pinos da Ponte H
#define PH_IN1 5
#define PH_IN2 6
#define PH_IN3 9
#define PH_IN4 10

void configura_velocidade (int motor_a, int motor_b)
{
	if(motor_a > 0)
	{
		analogWrite(PH_IN1, motor_a);
		analogWrite(PH_IN2, 0);
	}
	else
	{
		analogWrite(PH_IN1, 0);
		analogWrite(PH_IN2, -motor_a);
	}

	if(motor_b > 0)
	{
		analogWrite(PH_IN3, motor_b);
		analogWrite(PH_IN4, 0);
	}
	else
	{
		analogWrite(PH_IN3, 0);
		analogWrite(PH_IN4, -motor_b);
	}
}

void setup()
{
	pinMode(PH_IN1, OUTPUT);
	pinMode(PH_IN2, OUTPUT);
	pinMode(PH_IN3, OUTPUT);
	pinMode(PH_IN4, OUTPUT);
	Serial.begin(9600);
}

void loop()
{
	configura_velocidade(0,0);
	for(int i = 0; i < 256; i += 2)
	{
		configura_velocidade(i,i);
		delay(1000);
		Serial.println("i = " + i);
	}
}
