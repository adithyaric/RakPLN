/* Program Arduino Material Rak PLN
 * Code By : Jasa Pembuatan Program Arduino IOT
 * Made By : Agung Sidiq Santoso
 * Address : Grabag, Magelang, Jawa Tengah
 */
 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Sim800L.h>
#include <Keypad.h>
#include <jled.h>
#include "Adafruit_Thermal.h"
#include <EEPROM.h>
#include <Arduino_JSON.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Serial 3 -> Ke Serial3

//Serial 2
#define RX  17
#define TX  16
Sim800L GSM(RX, TX);

//Serial1
Adafruit_Thermal printer(&Serial1);

auto led = JLed(12).Blink(300, 300).Repeat(5);

char* pesan;
char* nomor = "";
bool terkirim;

char key;
String teksNIM = "";
String teksIdAmbil = "";
String teksIdTambah = "";
String teksIdLihat = "";
String teksJmlAmbil = "";
String teksJmlTambah = "";
String teksNoHP = "";

String nim = "";

byte menu = 0;

String semuaData;
boolean pecah = false;

String id_barang, tgl_update, status_update, nama_barang, satuan_barang, jumlah_barang, kode_rak;

void setup() {
  Serial.begin(9600);
  GSM.begin(4800);
  Serial3.begin(115200);
  Serial1.begin(19200);
  printer.begin();
  
  lcd.begin();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  menuUtama :
  key = keypad.getKey();

  if(terkirim) {
    led.Update();
  }

  if(key){ //Atur NIM
    if(key == 'A') {
      nim = "";
      lcd.clear();
      while(1) {
        key = keypad.getKey();

        lcd.setCursor(4,0);
        lcd.print(F("INPUT BIODATA"));
        
        lcd.setCursor(0,1);
        lcd.print(F("Nama: "));
        lcd.print(F("Zaelani"));

        lcd.setCursor(0,2);
        lcd.print(F("Nim : "));

        lcd.setCursor(0,3);
        lcd.print(F("Batal(*) Simpan(#)"));

        if(key) {
          if(key == '*') {
            teksNIM = "";
            lcd.setCursor(6,2);
            lcd.print(F("              "));
          }else if(key == '#'){
            nim += teksNIM;
            pesan = "Nim telah diubah";
            //terkirim = GSM.sendSms(nomor,pesan);
            teksNIM = "";
            lcd.clear();
            break;
          }else if(key == 'A'){
            lcd.clear();
            break;
          }else if((key == 'B') ||(key == 'C') || (key == 'D')) {
            // Tidak ada
          }else{
            teksNIM += key;
            lcd.setCursor(6, 2);
            lcd.print(teksNIM);
          }
        }
      }
    }else if(key == 'B') { //Tambah Jumlah Barang yang sudah ada
      lcd.clear();
      while(1) {
        key = keypad.getKey();

        lcd.setCursor(0,0);
        lcd.print(F("Ambil Jml Barang"));
        
        lcd.setCursor(0,1);
        lcd.print(F("ID : "));

        if(key) {
          if(key == '*') {
            teksIdAmbil = "";
            lcd.setCursor(5,1);
            lcd.print(F("      "));
          }else if(key == '#') {
            while(1) {
              key = keypad.getKey();
              
              lcd.setCursor(0,2);
              lcd.print(F("Jumlah : "));

              if(key) {
                if(key == '*') {
                  teksJmlAmbil = "";
                  lcd.setCursor(9,2);
                  lcd.print(F("      "));
                }else if(key == '#') {
                  Serial3.println("get," + 
                                  teksIdAmbil + "," +
                                  teksJmlAmbil);
                  lcd.clear();
                  while(1) {
                    key = keypad.getKey();
                    //Print data dan kirim SMS

                    if(Serial3.available()) {
                      char data = (char)Serial3.read();
                      semuaData += data;
                      if(data == '\n') pecah = true;
                    }
      
                    if(pecah) {
                      Serial.println(semuaData);
                      JSONVar doc = JSON.parse(semuaData); 
      
                      if (doc.hasOwnProperty("id")) id_barang = doc["id"];
                      if (doc.hasOwnProperty("tgl_update")) tgl_update = doc["tgl_update"];
                      if (doc.hasOwnProperty("status_update")) status_update = doc["status_update"];
                      if (doc.hasOwnProperty("nama_barang")) nama_barang = doc["nama_barang"];
                      if (doc.hasOwnProperty("satuan_barang")) satuan_barang = doc["satuan_barang"];
                      if (doc.hasOwnProperty("jumlah_barang")) jumlah_barang = doc["jumlah_barang"];
                      if (doc.hasOwnProperty("kode_rak")) kode_rak = doc["kode_rak"];
                      
                      lcd.setCursor(0,0);
                      lcd.print(F("ID:"));
                      lcd.print(id_barang);
                      lcd.print(F(" ("));
                      lcd.print(nama_barang);
                      lcd.print(F(")"));
      
                      lcd.setCursor(12,0);
                      lcd.print(F("("));
                      lcd.print(satuan_barang);
                      lcd.print(F(")"));
      
                      lcd.setCursor(0,1);
                      lcd.print(F("Get:"));
                      lcd.print(teksJmlAmbil);
      
                      lcd.setCursor(9, 1);
                      lcd.print(F("Sisa:"));
                      lcd.print(jumlah_barang);
      
                      lcd.setCursor(0, 2);
                      lcd.print(F("Rak:"));
                      lcd.print(kode_rak);
      
                      lcd.setCursor(0, 3);
                      lcd.print(tgl_update);
                      
                      pesan = "Barang sudah diambil";
                      //terkirim = GSM.sendSms(nomor,pesan);

//                      printer.wake();
//                      printer.setDefault();
//                      printer.justify('C');
//                      printer.setSize('L');
//                      printer.println("Material PLN\n");
//                      printer.println("By : Zaelani\n");
//                      printer.println(nim);
//                      printer.println("\n");
//
//                      printer.println("Status Update : ");
//                      printer.println(status_update);
//                      printer.println("\n");
//
//                      printer.println("Tanggal Update : ");
//                      printer.println(tgl_update);
//                      printer.println("\n");
//                      
//                      printer.justify('L');
//                      printer.setSize('S');
//                      printer.println("ID Material : ");
//                      printer.println(id_barang);
//                      printer.println("\n");
//                      
//                      printer.println("Nama Material : ");
//                      printer.println(nama_barang);
//                      printer.println("\n");
//                      
//                      printer.println("Jumlah Material : ");
//                      printer.println(jumlah_barang);
//                      printer.println(" ");
//                      printer.println(satuan_barang);
//                      printer.println("\n");
//
//                      printer.println("Jumlah Ambil : ");
//                      printer.println(teksJmlAmbil);
//                      printer.println(" ");
//                      printer.println(satuan_barang);
//                      printer.println("\n");
//                      
//                      printer.println("Kode Rak : ");
//                      printer.println(kode_rak);
//                      printer.println("\n");
//                      printer.sleep();
      
                      pecah = false;
                      semuaData = "";
                    }
                    
                    if(key == '*') {
                      lcd.clear();
                      teksIdAmbil = "";
                      teksJmlAmbil = "";
                      goto menuUtama;
                    }
                  }
                }else if(key == 'B') {
                  teksIdAmbil = "";
                  teksJmlAmbil = "";
                  lcd.clear();
                  break;
                }else if((key == 'A') ||(key == 'C') || (key == 'D')) {
                  // Tidak ada
                }else{
                  teksJmlAmbil += key;
                  lcd.setCursor(9,2);
                  lcd.print(teksJmlAmbil);
                }
              }
            }
          }else if(key == 'B'){
            teksIdAmbil = "";
            lcd.clear();
            break;
          }else if((key == 'A') ||(key == 'C') || (key == 'D')) {
            // Tidak ada
          }else{
            teksIdAmbil += key;
            lcd.setCursor(5, 1);
            lcd.print(teksIdAmbil);
          }
        }
      }
    }else if(key == 'C') {
      lcd.clear();
      while(1) {
        key = keypad.getKey();

        lcd.setCursor(0,0);
        lcd.print(F("Tambah Jml Barang"));
        
        lcd.setCursor(0,1);
        lcd.print(F("ID : "));

        if(key) {
          if(key == '*') {
            teksIdTambah = "";
            lcd.setCursor(5,1);
            lcd.print(F("      "));
          }else if(key == '#') {
            while(1) {
              key = keypad.getKey();
              
              lcd.setCursor(0,2);
              lcd.print(F("Jumlah : "));

              if(key) {
                if(key == '*') {
                  teksJmlTambah = "";
                  lcd.setCursor(9,2);
                  lcd.print(F("      "));
                }else if(key == '#') {
                  Serial3.println("add," + 
                                  teksIdTambah + "," +
                                  teksJmlTambah);
                  lcd.clear();
                  while(1) {
                    key = keypad.getKey();
                    //Print data dan kirim SMS

                    if(Serial3.available()) {
                      char data = (char)Serial3.read();
                      semuaData += data;
                      if(data == '\n') pecah = true;
                    }
      
                    if(pecah) {
                      Serial.println(semuaData);
                      JSONVar doc = JSON.parse(semuaData); 
      
                      if (doc.hasOwnProperty("id")) id_barang = doc["id"];
                      if (doc.hasOwnProperty("tgl_update")) tgl_update = doc["tgl_update"];
                      if (doc.hasOwnProperty("status_update")) status_update = doc["status_update"];
                      if (doc.hasOwnProperty("nama_barang")) nama_barang = doc["nama_barang"];
                      if (doc.hasOwnProperty("satuan_barang")) satuan_barang = doc["satuan_barang"];
                      if (doc.hasOwnProperty("jumlah_barang")) jumlah_barang = doc["jumlah_barang"];
                      if (doc.hasOwnProperty("kode_rak")) kode_rak = doc["kode_rak"];
                      
                      lcd.setCursor(0,0);
                      lcd.print(F("ID:"));
                      lcd.print(id_barang);
                      lcd.print(F(" ("));
                      lcd.print(nama_barang);
                      lcd.print(F(")"));
      
                      lcd.setCursor(12,0);
                      lcd.print(F("("));
                      lcd.print(satuan_barang);
                      lcd.print(F(")"));
      
                      lcd.setCursor(0,1);
                      lcd.print(F("Add:"));
                      lcd.print(teksJmlTambah);
      
                      lcd.setCursor(9, 1);
                      lcd.print(F("Sisa:"));
                      lcd.print(jumlah_barang);
      
                      lcd.setCursor(0, 2);
                      lcd.print(F("Rak:"));
                      lcd.print(kode_rak);
      
                      lcd.setCursor(0, 3);
                      lcd.print(tgl_update);
                      
                      pesan = "Barang sudah ditambah";
                      //terkirim = GSM.sendSms(nomor,pesan);

//                      printer.wake();
//                      printer.setDefault();
//                      printer.justify('C');
//                      printer.setSize('L');
//                      printer.println("Material PLN\n");
//                      printer.println("By : Zaelani\n");
//                      printer.println(nim);
//                      printer.println("\n");
//
//                      printer.println("Status Update : ");
//                      printer.println(status_update);
//                      printer.println("\n");
//
//                      printer.println("Tanggal Update : ");
//                      printer.println(tgl_update);
//                      printer.println("\n");
//                      
//                      printer.justify('L');
//                      printer.setSize('S');
//                      printer.println("ID Material : ");
//                      printer.println(id_barang);
//                      printer.println("\n");
//                      
//                      printer.println("Nama Material : ");
//                      printer.println(nama_barang);
//                      printer.println("\n");
//                      
//                      printer.println("Jumlah Material : ");
//                      printer.println(jumlah_barang);
//                      printer.println(" ");
//                      printer.println(satuan_barang);
//                      printer.println("\n");
//
//                      printer.println("Jumlah Tambah : ");
//                      printer.println(teksJmlTambah);
//                      printer.println(" ");
//                      printer.println(satuan_barang);
//                      printer.println("\n");
//                      
//                      printer.println("Kode Rak : ");
//                      printer.println(kode_rak);
//                      printer.println("\n");
//                      printer.sleep();
      
                      pecah = false;
                      semuaData = "";
                    }
                    
                    if(key == '*') {
                      lcd.clear();
                      teksIdTambah = "";
                      teksJmlTambah = "";
                      goto menuUtama;
                    }
                  }
                }else if(key == 'C') {
                  teksIdTambah = "";
                  teksJmlTambah = "";
                  lcd.clear();
                  break;
                }else if((key == 'A') ||(key == 'B') || (key == 'D')) {
                  // Tidak ada
                }else{
                  teksJmlTambah += key;
                  lcd.setCursor(9,2);
                  lcd.print(teksJmlTambah);
                }
              }
            }
          }else if(key == 'C'){
            teksIdTambah = "";
            lcd.clear();
            break;
          }else if((key == 'A') ||(key == 'B') || (key == 'D')) {
            // Tidak ada
          }else{
            teksIdTambah += key;
            lcd.setCursor(5, 1);
            lcd.print(teksIdTambah);
          }
        }
      }
    }else if(key == 'D') {
      lcd.clear();
      while(1) {
        key = keypad.getKey();

        lcd.setCursor(0,0);
        lcd.print(F("Lihat Barang"));
        
        lcd.setCursor(0,1);
        lcd.print(F("ID : "));

        if(key) {
          if(key == '*') {
            teksIdLihat = "";
            lcd.setCursor(5,1);
            lcd.print(F("      "));
          }else if(key == '#') {
            Serial3.println("lihat," + 
                            teksIdLihat + ",999");
            lcd.clear();
            while(1) {
              key = keypad.getKey();
              
              if(Serial3.available()) {
                char data = (char)Serial3.read();
                semuaData += data;
                if(data == '\n') pecah = true;
              }

              if(pecah) {
                Serial.println(semuaData);
                JSONVar doc = JSON.parse(semuaData); 

                if (doc.hasOwnProperty("id")) id_barang = doc["id"];
                if (doc.hasOwnProperty("tgl_update")) tgl_update = doc["tgl_update"];
                if (doc.hasOwnProperty("status_update")) status_update = doc["status_update"];
                if (doc.hasOwnProperty("nama_barang")) nama_barang = doc["nama_barang"];
                if (doc.hasOwnProperty("satuan_barang")) satuan_barang = doc["satuan_barang"];
                if (doc.hasOwnProperty("jumlah_barang")) jumlah_barang = doc["jumlah_barang"];
                if (doc.hasOwnProperty("kode_rak")) kode_rak = doc["kode_rak"];
                
                lcd.setCursor(0,0);
                lcd.print(F("ID:"));
                lcd.print(id_barang);
                lcd.print(F(" ("));
                lcd.print(nama_barang);
                lcd.print(F(")"));

                lcd.setCursor(0, 1);
                lcd.print(F("Sisa:"));
                lcd.print(jumlah_barang);
                lcd.print(F(" "));
                lcd.print(satuan_barang);

                lcd.setCursor(0, 2);
                lcd.print(F("Rak:"));
                lcd.print(kode_rak);

                lcd.setCursor(0, 3);
                lcd.print(tgl_update);

                pecah = false;
                semuaData = "";
              }
              
              if(key == '*') {
                lcd.clear();
                teksIdLihat = "";
                goto menuUtama;
              }
            }
          }else if(key == 'D'){
            teksIdLihat = "";
            lcd.clear();
            break;
          }else if((key == 'A') ||(key == 'B') || (key == 'C')) {
            // Tidak ada
          }else{
            teksIdLihat += key;
            lcd.setCursor(5, 1);
            lcd.print(teksIdLihat);
          }
        }
      }
    }
  }
  
  lcd.setCursor(0,0);
  lcd.print(F("Database Material"));
  
  lcd.setCursor(0,1);
  lcd.print(F("Nama: "));
  lcd.print(F("Zaelani"));

  lcd.setCursor(0,2);
  lcd.print(F("Nim : "));
  lcd.print(nim);

  lcd.setCursor(0,3);
  lcd.print(F("Menu -> A B C D"));
}

long EEPROMReadlong(long address) {
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

void EEPROMWritelong(int address, long value) {
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}
