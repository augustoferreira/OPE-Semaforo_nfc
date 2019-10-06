#include <SPI.h>
#include <MFRC522.h>

#define SS 10
#define RST 9

MFRC522 sensor(SS, RST);   
 

 
char st[20];

void setup()
{
  pinMode(1, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, INPUT);
  Serial.begin(9600);   
  SPI.begin();      
  sensor.PCD_Init();  
  Serial.println("Aproxime a Tag do leitor por favor...");
  Serial.println();
  pinMode(7, INPUT);
  
}

void loop()
{
  // Look for new cards
  if ( ! sensor.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! sensor.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("ID  :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < sensor.uid.size; i++) 
  {
     Serial.print(sensor.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(sensor.uid.uidByte[i], HEX);
     conteudo.concat(String(sensor.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(sensor.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
{
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  delay(5000); // Wait for 1000 millisecond(s)
  digitalWrite(1, LOW);
  digitalWrite(3, HIGH);
  delay(5000); // Wait for 1000 millisecond(s)
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  delay(5000); // Wait for 1000 millisecond(s)
  digitalWrite(6, LOW);
  digitalWrite(4, HIGH);
  delay(5000);
  
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}
  
  
  if (conteudo.substring(1) == "F7 9C 44 DE") //ID 1 - bom
{
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  delay(10000); // Wait for 1000 millisecond(s)
  digitalWrite(1, LOW);
  digitalWrite(3, HIGH);
  delay(10000); // Wait for 1000 millisecond(s)
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  delay(10000); // Wait for 1000 millisecond(s)
  digitalWrite(6, LOW);
  digitalWrite(4, HIGH);
  delay(10000);
  
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

}
