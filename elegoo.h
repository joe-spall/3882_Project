#define RIGHT_MOTORS 6
#define LEFT_MOTORS 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11


class Elegoo
{
	public:
		Elegoo();
		// Motor Control
		motorForward(float pwrLeft, float pwrRight);
		motorBackward(float pwrLeft, float pwrRight);
		motorLeft(float pwrLeft, float pwrRight);
		motorRight(float pwrLeft, float pwrRight);
		motorStop();
}