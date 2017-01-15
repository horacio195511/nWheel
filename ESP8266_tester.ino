void setup() {
  Serial.begin(9660);
  Serial1.begin(9600);
  Serial.println("Serial has initialized.");
  pinMode(13,OUTPUT);
}

void loop() {
  Serial1.write("AT\n\r");
  digitalWrite(13,HIGH);  
  while(!Serial1.available()){}
  
  while(Serial1.available()){
    digitalWrite(13,LOW);
    int esp;
    esp=Serial1.read();
    Serial.print(esp);
  }
}
