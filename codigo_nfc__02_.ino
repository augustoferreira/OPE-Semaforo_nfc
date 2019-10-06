/* Programa de Dump da etiqueta NFC NTAG213
  Blog Eletrogate - https://blog.eletrogate.com/guia-basico-da-nfc-para-arduino
  Arduino UNO - IDE 1.8.5 - Modulo RC522
  Gustavo Murta   06/maio/2018
  Biblioteca MFRC522 https://github.com/miguelbalboa/rfid     Baseado no exemplo DumpInfo.ino
*/
 
#include <SPI.h>                                              // Biblioteca SPI 
#include <MFRC522.h>                                          // Biblioteca MFRC522
 
int RST_PIN = 9;                                              // pino Reset - pino D9 do Arduino
int SS_PIN = 10;                                              // pino SS ou SDA - pino D10 do Arduino
 
MFRC522 mfrc522(SS_PIN, RST_PIN);                             // cria instancia MFRC522
 
void setup() {
  Serial.begin(9600);                                      // inicializa a comunicação serial com o PC
  while (!Serial);                                          // aguarda a abertura da interface serial
  SPI.begin();                                            // inicializa o barramento SPI
  mfrc522.PCD_Init();                                       // inicializa o modulo RC522
  mfrc522.PCD_DumpVersionToSerial();                        // mostra as informções do modulo RC522
  Serial.println("Lendo a etiqueta NTAG213 =  UID, SAK, tipo e blocos de dados...");
}
 
void dumpNTAG213 ()
{
  byte byteCount;                                             // contador de bytes
  byte buffer[18];                                            // 16 bytes de dados mais 2 bytes de CRC
  byte i;                                                     // indice
  byte Status;                                                // código do status
 
  Serial.println("Page  0  1  2  3");                         // imprime o cabeçalho da tabela
  for (byte page = 0; page < 45; page += 4)                   // NTAG213 possui 45 paginas
  {
    byteCount = sizeof(buffer);                               // tamanho do buffer = 18 bytes
    Status = mfrc522.MIFARE_Read(page, buffer, &byteCount);   // lendo 4 bytes por pagina
    if (Status != 0)                                          // STATUS_OK = 0
    {
      Serial.print("Leitura da etiqueta falhou = ");          // imprime monitor serial
      Serial.println(mfrc522.GetStatusCodeName(Status));      // imprime o código da falha de leitura
      break;
    }
    for (byte offset = 0; offset < 4; offset++)               // contando os bytes das paginas
    {
      i = page + offset;
      if (i < 10)
        Serial.print("  ");                                   // imprimindo espaço
      else
        Serial.print(" ");                                    // imprimindo espaço
      if (i < 45)                                             // no maximo 45 paginas de dados
      {
        Serial.print(i);                                      // imprimindo o endereço da pagina
        Serial.print("  ");
        for (byte index = 0; index < 4; index++)              // indexando os bytes de enedereço
        {
          i = 4 * offset + index;
          if (buffer[i] < 0x10)                               // imprimindo o buffer 16 bytes
            Serial.print(" 0");
          else
            Serial.print(" ");                                // imprimindo espaço
          Serial.print(buffer[i], HEX);                       // imprimindo os bytes da memoria
        }
        Serial.println();                                     // salta uma linha
      }
    }
  }
}
 
void loop()
{
  if ( ! mfrc522.PICC_IsNewCardPresent())                    // Verificando novas etiquetas NFC
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())                      // Seleciona uma etiqueta NFC
  {
    return;
  }
  dumpNTAG213 ();                                            // imprime dados da NTAG213
  Serial.println();                                          // salta uma linha
  delay(1000);                                               // atraso de um segundo
}
 
