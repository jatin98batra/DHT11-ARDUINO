double exiting, entring;
#define DataLine 7
uint8_t data = 0, Hum_High = 0, Hum_Low = 0, Temp_High = 0, Temp_Low = 0, Checksum = 0;
void setup()
  {
    Serial.begin(9600);
    Serial.println("::::::::::::::::::::::::Weather Station::::::::::::::::");
    delay(2000);
  }

void loop()
  {
    Request();
    Response();
    Hum_High = RecData();
    Hum_Low = RecData();
    Temp_High = RecData();
    Temp_Low = RecData();
    Checksum = RecData();
  if ((Hum_High + Hum_Low + Temp_High + Temp_Low) != Checksum)
        Serial.println("Error");
  else
    {
        Serial.print("Humidity:");
        Serial.print(Hum_High);
        Serial.print(".");
        Serial.print(Hum_Low);
        Serial.println("%");
        Serial.print("Temprature:");
        Serial.print(Temp_High);
        Serial.print(".");
        Serial.print(Temp_Low);
        Serial.println(" C");
        Serial.println("===============================");
    }

  delay(2000);
    }

//Function definitions

void Request()
{
  pinMode(DataLine, OUTPUT);
  digitalWrite(DataLine, LOW);
  delay(22);//Wait For more than 18ms
  digitalWrite(DataLine, HIGH);
  delayMicroseconds(28);
}

void Response()
{
  pinMode(DataLine, INPUT);
  while ((digitalRead(DataLine) == HIGH)); //Change of Signal... Pulled High
  while ((digitalRead(DataLine) == LOW)); //80uS
  while ((digitalRead(DataLine) == HIGH)); //80uS: So if this ends , this means that its definitly LOW on DataLine Now

}

uint8_t RecData()
{
  int i;
  for (i = 0; i < 8; i++)
  {
    while ((digitalRead(DataLine) == LOW));
    delayMicroseconds(30);
    if ((digitalRead(DataLine) == HIGH))
      //Its a HIGH
    {
      data = data << 1; //MSB First
      data = data | 0x01; //Writing to the last bit
    }
    else
      // LOW Case
      data = data << 1;
    while ((digitalRead(DataLine) == HIGH)); //Doesn't Matter How Long it Goes ..(Bad Programming)
  }
  return data;
}



