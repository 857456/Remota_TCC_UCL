#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>


modbusDevice regBank;
modbusSlave slave;

word AI0, AI1, AI2, AI3, AI4, AI5;

void setup() {
  //Set Slave ID
  regBank.setId(1);  //Set Slave ID

  //Add Digital Output registers
  regBank.add(28);
  regBank.add(26);
  regBank.add(24);
  regBank.add(22);

  //Add Digital Input registers
  regBank.add(10002);
  regBank.add(10003);
  regBank.add(10004);
  regBank.add(10005);
  regBank.add(10006);
  regBank.add(10007);

  //Analog Input registers
  regBank.add(30001);
  regBank.add(30002);
  regBank.add(30003);
  regBank.add(30004);

  //Analog Output registers
  regBank.add(40002);
  regBank.add(40003);
  regBank.add(40004);
  regBank.add(40005);
  regBank.add(40006);
  regBank.add(40007);

  slave._device = &regBank;

  //Set BaudRate
  slave.setBaud(9600);

  //Configure pins
  pinMode(42, INPUT);   //DI0
  pinMode(44, INPUT);   //DI1
  pinMode(46, INPUT);   //DI2
  pinMode(48, INPUT);   //DI3
  pinMode(50, INPUT);   //DI4
  pinMode(52, INPUT);   //DI5
  pinMode(28, OUTPUT);  //DO0
  pinMode(26, OUTPUT);  //DO1
  pinMode(24, OUTPUT);  //DO2
  pinMode(22, OUTPUT);  //DO3
}

void loop() {
  while (1) {


    //Digital Output
    byte DO0 = regBank.get(28);
    if (DO0 <= 0 && digitalRead(28) == HIGH) digitalWrite(28, LOW);
    if (DO0 >= 1 && digitalRead(28) == LOW) digitalWrite(28, HIGH);

    byte DO1 = regBank.get(26);
    if (DO1 <= 0 && digitalRead(26) == HIGH) digitalWrite(26, LOW);
    if (DO1 >= 1 && digitalRead(26) == LOW) digitalWrite(26, HIGH);

    byte DO2 = regBank.get(24);
    if (DO2 <= 0 && digitalRead(24) == HIGH) digitalWrite(24, LOW);
    if (DO2 >= 1 && digitalRead(24) == LOW) digitalWrite(24, HIGH);

    byte DO3 = regBank.get(22);
    if (DO3 <= 0 && digitalRead(22) == HIGH) digitalWrite(22, LOW);
    if (DO3 >= 1 && digitalRead(22) == LOW) digitalWrite(22, HIGH);


    //Digital Input
    byte DI0 = digitalRead(42);
    if (DI0 >= 1) regBank.set(10002, 1);
    if (DI0 <= 0) regBank.set(10002, 0);

    byte DI1 = digitalRead(44);
    if (DI1 >= 1) regBank.set(10003, 1);
    if (DI1 <= 0) regBank.set(10003, 0);

    byte DI2 = digitalRead(46);
    if (DI2 >= 1) regBank.set(10004, 1);
    if (DI2 <= 0) regBank.set(10004, 0);

    byte DI3 = digitalRead(48);
    if (DI3 >= 1) regBank.set(10005, 1);
    if (DI3 <= 0) regBank.set(10005, 0);

    byte DI4 = digitalRead(50);
    if (DI4 >= 1) regBank.set(10006, 1);
    if (DI4 <= 0) regBank.set(10006, 0);

    byte DI5 = digitalRead(52);
    if (DI5 >= 1) regBank.set(10007, 1);
    if (DI5 <= 0) regBank.set(10007, 0);


    //Analog Input
    AI0 = analogRead(A0);  //Potenciometro1
    delay(10);
    AI0 = analogRead(A0);
    regBank.set(30001, (word)AI0);
    delay(10);

    AI1 = analogRead(A1);  //Potenciometro2
    delay(10);
    AI1 = analogRead(A1);
    regBank.set(30002, (word)AI1);
    delay(10);

    AI3 = analogRead(A3);  //Potenciometro3
    delay(10);
    AI3 = analogRead(A3);
    regBank.set(30003, (word)AI3);
    delay(10);

    AI4 = analogRead(A4);  //Potenciometro4
    delay(10);
    AI4 = analogRead(A4);
    regBank.set(30004, (word)AI4);
    delay(10);


    // Analog Output (PWM)
    word AO0 = regBank.get(40002);
    analogWrite(2, AO0);
    delay(10);

    word AO1 = regBank.get(40003);
    analogWrite(3, AO1);
    delay(10);

    word AO2 = regBank.get(40004);
    analogWrite(4, AO2);
    delay(10);

    word AO3 = regBank.get(40005);
    analogWrite(5, AO3);
    delay(10);

    word AO4 = regBank.get(40006);
    analogWrite(6, AO4);
    delay(10);

    word AO5 = regBank.get(40007);
    analogWrite(7, AO5);
    delay(10);


    slave.run();
  }
}
