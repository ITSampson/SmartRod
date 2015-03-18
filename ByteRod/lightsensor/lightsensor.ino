int lightLevel; 

void setup()
{
  Serial.begin(38400);
}

void loop() 
{
  lightLevel = analogRead(A3);
  Serial.println(lightLevel, DEC);
  delay(200);
}
