// Definimos los pines donde tenemos conectadas las bobinas
#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11
//uencia de pasos (par máximo)
int paso [4][4] =
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};
int paso2 [4][4] =
{
  {0, 0, 0, 1},
  {0, 0, 1, 0},
  {0, 1, 0, 0},
  {1, 0, 0, 0}
};

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600); //bitrate
}


void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()>0){
    int sel = Serial.read();
/*    for (int j = 0; j<500; j++){
      for (int i = 0; i < 4; i++)
        {
          digitalWrite(IN1, paso[i][0]);
          digitalWrite(IN2, paso[i][1]);
          digitalWrite(IN3, paso[i][2]);
          digitalWrite(IN4, paso[i][3]);
          delay(2);
        }
    }*/

for(int y = 0; y<2; y++){
for(int x = 0; x<2; x++){
for (int j = 0; j<10; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(2);
    }
}
    delay(200);
}

delay(400);
}

for (int j = 0; j<100; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(2);
    }
}
delay(150);

for(int x = 0; x<2; x++){
for (int j = 0; j<10; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(2);
    }
}
    delay(200);
}

delay(400);

for (int j = 0; j<20; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(2);
    }
}

delay(100);

for(int x = 0; x<2; x++){
for (int j = 0; j<10; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(2);
    }
}
    delay(50);
}

for (int j = 0; j<100; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(2);
    }
}
delay(100);
for (int x = 0; x<3; x++){
for (int j = 0; j<10; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(2);
    }
}
delay(100);
if(x<2){
for(int j = 0; j<10; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso2[i][0]);
      digitalWrite(IN2, paso2[i][1]);
      digitalWrite(IN3, paso2[i][2]);
      digitalWrite(IN4, paso2[i][3]);
      delay(2);
    }
}
delay(100);
}else{
for(int j = 0; j<25; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso2[i][0]);
      digitalWrite(IN2, paso2[i][1]);
      digitalWrite(IN3, paso2[i][2]);
      digitalWrite(IN4, paso2[i][3]);
      delay(2);
    }
} 
  }
}
delay(100);

for (int x = 0; x<5; x++){
for (int j = 0; j<10; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(2);
    }
}
delay(100);

for(int j = 0; j<10; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso2[i][0]);
      digitalWrite(IN2, paso2[i][1]);
      digitalWrite(IN3, paso2[i][2]);
      digitalWrite(IN4, paso2[i][3]);
      delay(2);
    }
}
delay(100);
}

for(int j = 0; j<25; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso2[i][0]);
      digitalWrite(IN2, paso2[i][1]);
      digitalWrite(IN3, paso2[i][2]);
      digitalWrite(IN4, paso2[i][3]);
      delay(2);
    }
}
delay(200);
for (int j = 0; j<10; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(2);
    }
}
delay(100);
for(int j = 0; j<100; j++){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso2[i][0]);
      digitalWrite(IN2, paso2[i][1]);
      digitalWrite(IN3, paso2[i][2]);
      digitalWrite(IN4, paso2[i][3]);
      delay(2);
    }
}

delay(1000);

  }
}
