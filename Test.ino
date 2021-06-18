#include <LiquidCrystal.h>

// инициализация пинов дисплея 
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

long randNumber; // переменная для выбора светодиода
int waitTime; // пауза разной величины перед включением светодиода
int startTime; // начало отсчёта

int reactionTime; // время реакции
int counter = 1; // счетчик попыток

int piezoPin = 13;
const int ledPin1 = 8; // светодиод 1
const int ledPin2 = 9; 
const int ledPin3 = 10; 
const int ledPin4 = 11; 
const int ledPin5 = 12; 
const int buttonPin1 = A1; // кнопка 1
const int buttonPin2 = A2; 
const int buttonPin3 = A3; 
const int buttonPin4 = A4; 
const int buttonPin5 = A5; 

int ledState1 = 0; // текущее состояние светодиод 1
int ledState2 = 0; 
int ledState3 = 0; 
int ledState4 = 0; 
int ledState5 = 0; 
boolean buttonWasUp = true; // состояние для кнопки вкл

void setup(){

Serial.begin(9600);
Serial.println("CLEARDATA"); // команда очистки таблицы Excel
Serial.println("LABEL,Date,Time,TRY,R Time"); // команда создания заголовков таблицы Excel
Serial.println("RESETTIMER");
pinMode(13, OUTPUT);
pinMode(ledPin1, OUTPUT); // задача режима работы пина светодиода
pinMode(ledPin2, OUTPUT); 
pinMode(ledPin3, OUTPUT); 
pinMode(ledPin4, OUTPUT);
pinMode(ledPin5, OUTPUT);
pinMode(buttonPin1, INPUT_PULLUP);// задача режима работы пина кнопки
pinMode(buttonPin2, INPUT_PULLUP);
pinMode(buttonPin3, INPUT_PULLUP);
pinMode(buttonPin4, INPUT_PULLUP);
pinMode(buttonPin5, INPUT_PULLUP);
pinMode(A0, INPUT_PULLUP); // задача режима работы для кнопки вкл

// команда инициализации экрана 16х2
lcd.begin(16, 2);
// команды вывода сообщений на экран дисплея
lcd.print("Welcome to the");
lcd.setCursor(0,2 );
lcd.print("reaction test");
delay(2000);
lcd.clear();// команда очистки дисплея
lcd.setCursor(0,0 );
lcd.print("Made by ");
delay(1000);
lcd.clear();
lcd.setCursor(0,0 );
lcd.print("4th year student");
lcd.setCursor(0,1 );
lcd.print("Selutin Denis"); 
delay(3000);
lcd.clear();
lcd.setCursor(0,0 );
lcd.print("Starting ");
lcd.setCursor(0,1 );
lcd.print("the test...");
delay(2000);  
lcd.clear();
lcd.setCursor(0,0 );
lcd.print("Press start ");
lcd.setCursor(0,1 );
lcd.print("button to begin");
delay(2000);
lcd.clear();
}

void loop()
{
// цикл для начала тестирвования
boolean buttonIsUp = digitalRead(A0);
if (buttonWasUp && !buttonIsUp) {
delay(10);
buttonIsUp = digitalRead(7); 
while(!buttonIsUp) {
  
while (counter <= 10) { 
// Печать сообщений на дисплей
lcd.print("TRY number:");
lcd.print(counter);
delay(1000);
lcd.clear();
// Print a message to the LCD.
// lcd.begin(16, 2);
lcd.print("READY? - GO!   ");
delay(500); 
// set up the LCD's number of columns and rows:
randNumber = random (8, 13);
Serial.print("TRY :   ");
Serial.print(counter);
Serial.print("      READY? - GO!   ");
waitTime = random(1000, 5000); // пауза в виде случайной величины от 2000 до 4000 мс
delay(waitTime); // делаем паузу
digitalWrite(randNumber, HIGH); // включаем светодиод

tone(piezoPin, 1000, 50);
delay(10);
// считываение состояния светодиода
ledState1 = digitalRead(ledPin1);


startTime = millis(); // запоминаем начальное время
// выключение светодиода при нажатии
// если кнопка нажата, то её состояние HIGH:
if (ledState1 == HIGH) {
while (digitalRead(buttonPin1) == HIGH) {  }  // включаем светодиод
digitalWrite(ledPin1, LOW);
}

ledState2 = digitalRead(ledPin2);
// выключение светодиода при нажатии 
if (ledState2 == HIGH ) {
while (digitalRead(buttonPin2) == HIGH) {  }
digitalWrite(ledPin2, LOW);
}
ledState3 = digitalRead(ledPin3);

if (ledState3 == HIGH ) {
while (digitalRead(buttonPin3) == HIGH) {  }
digitalWrite(ledPin3, LOW);
}
ledState4 = digitalRead(ledPin4);

if (ledState4 == HIGH ) {
while (digitalRead(buttonPin4) == HIGH) {  }
digitalWrite(ledPin4, LOW);
}

ledState5 = digitalRead(ledPin5);
if (ledState5 == HIGH ) {
while (digitalRead(buttonPin5) == HIGH) {  }
digitalWrite(ledPin5, LOW);
}
reactionTime = millis()- startTime;
// set up the LCD's number of columns and rows:

// вывод показателей на дисплей
lcd.clear();        
lcd.print("R TIME:");
lcd.setCursor(0,2 );
lcd.print(reactionTime); 
lcd.print(" ms");

  
//reactionTime = millis()- startTime;
Serial.print("  R TIME:  ");
Serial.print(reactionTime);
Serial.println(" ms");
Serial.println("DATA,DATE,TIME,"+ String(counter)+ "," +String(reactionTime));
counter++;
delay(3000);
lcd.clear();
  
 } 
lcd.print("END OF TEST");
delay(2000);
lcd.clear(); 
}

}
buttonWasUp = buttonIsUp; // маркер кнопки включения
}
