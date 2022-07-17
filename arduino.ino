const int EnableL = 5;
const int HighL = 6; // LEFT SIDE MOTOR
const int LowL = 7;

const int EnableR = 10;
const int HighR = 8; // RIGHT SIDE MOTOR
const int LowR = 9;

const int D0 = 11; // Raspberry pin 21    LSB
const int D1 = 12; // Raspberry pin 22
const int D2 = 13; // Raspberry pin 23

const  int trigger=3;
const  int echo=2;

bool object_detection(){
    // Trigger the sensor to start measurement
    // Set up trigger
    digitalWrite(trigger,LOW);
    delayMicroseconds(5);
    
    //Start Measurement
    digitalWrite(trigger,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger,LOW);
    
    // Acquire and convert to inches
    float distance=pulseIn(echo,HIGH);
    distance=distance*0.0001657;
    float dist_inches=distance*39.37;
    
    return dist_inches < 5;
  }

void setup()
{

    // Set pinModes
    pinMode(EnableL, OUTPUT);
    pinMode(HighL, OUTPUT);
    pinMode(LowL, OUTPUT);

    pinMode(EnableR, OUTPUT);
    pinMode(HighR, OUTPUT);
    pinMode(LowR, OUTPUT);

    pinMode(D0, INPUT_PULLUP);
    pinMode(D1, INPUT_PULLUP);
    pinMode(D2, INPUT_PULLUP);
    
    pinMode(trigger,OUTPUT);
    pinMode(echo,INPUT);
}

int Data()
{
    int a = digitalRead(D0);
    int b = digitalRead(D1);
    int c = digitalRead(D2);
    int data = 4 * c + 2 * b + a;
    return data;
}

void Forward()
{
    digitalWrite(HighL, LOW);
    digitalWrite(LowL, HIGH);
    analogWrite(EnableL, 255);

    digitalWrite(HighR, LOW);
    digitalWrite(LowR, HIGH);
    analogWrite(EnableR, 255);
}

void Backward()
{
    digitalWrite(HighL, HIGH);
    digitalWrite(LowL, LOW);
    analogWrite(EnableL, 255);

    digitalWrite(HighR, HIGH);
    digitalWrite(LowR, LOW);
    analogWrite(EnableR, 255);
}

void Stop()
{
    digitalWrite(HighL, LOW);
    digitalWrite(LowL, HIGH);
    analogWrite(EnableL, 0);

    digitalWrite(HighR, LOW);
    digitalWrite(LowR, HIGH);
    analogWrite(EnableR, 0);
}

void Left(int left_motor, int right_motor)
{
    digitalWrite(HighL, LOW);
    digitalWrite(LowL, HIGH);
    analogWrite(EnableL, left_motor);

    digitalWrite(HighR, LOW);
    digitalWrite(LowR, HIGH);
    analogWrite(EnableR, right_motor);
}

void Right(int left_motor, int right_motor)
{
    digitalWrite(HighL, LOW);
    digitalWrite(LowL, HIGH);
    analogWrite(EnableL, left_motor);

    digitalWrite(HighR, LOW);
    digitalWrite(LowR, HIGH);
    analogWrite(EnableR, right_motor);
}

void UTurn()
{
    analogWrite(EnableL, 0);
    analogWrite(EnableR, 0);
    delay(400);

    analogWrite(EnableL, 250);
    analogWrite(EnableR, 250); // forward
    delay(1000);

    analogWrite(EnableL, 0);
    analogWrite(EnableR, 0);
    delay(400);

    digitalWrite(HighL, HIGH);
    digitalWrite(LowL, LOW);
    digitalWrite(HighR, LOW); //   left
    digitalWrite(LowR, HIGH);
    analogWrite(EnableL, 255);
    analogWrite(EnableR, 255);
    delay(700);

    analogWrite(EnableL, 0);
    analogWrite(EnableR, 0);
    delay(400);

    digitalWrite(HighL, LOW);
    digitalWrite(LowL, HIGH);
    digitalWrite(HighR, LOW); // forward
    digitalWrite(LowR, HIGH);
    analogWrite(EnableL, 255);
    analogWrite(EnableR, 255);
    delay(900);

    analogWrite(EnableL, 0);
    analogWrite(EnableR, 0);
    delay(400);

    digitalWrite(HighL, HIGH);
    digitalWrite(LowL, LOW);
    digitalWrite(HighR, LOW); // left
    digitalWrite(LowR, HIGH);
    analogWrite(EnableL, 255);
    analogWrite(EnableR, 255);
    delay(700);

    analogWrite(EnableL, 0);
    analogWrite(EnableR, 0);
    delay(1000);

    digitalWrite(HighL, LOW);
    digitalWrite(LowL, HIGH);
    digitalWrite(HighR, LOW);
    digitalWrite(LowL, HIGH);
    analogWrite(EnableL, 150);
    analogWrite(EnableR, 150);
    delay(300);
}

void loop()
{
    object_in_front = object_detection();
    if (object_in_front) {
        Stop();
    }
    else if(data==0)
    {
        Forward();
    }
    else if (data == 1)
    {
        Right(255, 100);
    }

    else if (data == 2)
    {
        Right(255, 50);
    }

    else if (data == 3)
    {
        Right(255, 0);
    }

    else if (data == 4)
    {
        Left(100, 255);
    }

    else if (data == 5)
    {
        Left(50, 255);
    }

    else if (data == 6)
    {
        Left(0, 255);
    }

    else if (data == 7)
    {
        UTurn();
    }

    else if (data > 7)
    {
        Stop();
    }
}
