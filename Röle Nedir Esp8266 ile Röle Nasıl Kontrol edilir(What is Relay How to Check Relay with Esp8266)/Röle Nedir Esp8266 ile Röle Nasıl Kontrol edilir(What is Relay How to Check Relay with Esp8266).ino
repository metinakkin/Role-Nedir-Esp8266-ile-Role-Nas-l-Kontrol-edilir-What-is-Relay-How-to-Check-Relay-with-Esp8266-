#define ag_ismi "*******"  //Wifi adı>>Wifi name
#define ag_sifresi "*******"  //Wifi şifresi>>Wifi password
#include<Servo.h>  //Servo kütüphanesi>>Servo library
int role=7;

void setup()
{
  Serial.begin(115200); //ESP modülünün baudRate değeri 115200 bu yüzden Seriport'u 115200 yazıyoruz>>The baud rate of the ESP module is 115200, so we write Seriport 115200
  pinMode(role, OUTPUT);                    
  Serial.println("AT"); //ESP modülümüz ile bağlantı kurulup kurulmadığını kontrol ediyoruz>>We check whether the Esp module is connected or not
   delay(3000); 
 
  if(Serial.find("OK"))//Eğer Esp8266 ile bağlantı kurulmuşsa "OK" komutu geri dönüş yapıyor>>If the Esp8266 is connected,the "OK" commands returns
  {         
     Serial.println("AT+CWMODE=1"); //Esp modülümüzün WiFi modunu STA şekline getiriyoruz ve wifiyi açıyoruz eğer=2 olursa wifiyi kapanır>>We bring STA the our wifi mode of Esp and open,if equal the 2,wifi is closed
     delay(2000);
     String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";//Wifiye bağlanmasını sağlıyoruz>>We provide connection
    Serial.println(baglantiKomutu);
     delay(5000);
 }
 
   Serial.print("AT+CIPMUX=1\r\n");//Çoklu bağlatıyı açıyoruz.>>We open multiple links.
   delay(200);
   Serial.print("AT+CIPSERVER=1,80\r\n");// Bağlantının açık olduğunu ve portunu söylüyoruz.>>We tell that connection is clear and port's value
   delay(1000);
}
void loop(){
  if(Serial.available()>0){
    if(Serial.find("+IPD,")){
      //Html kodlar
      String metin = "<head> Metin AKKIN </head>";//Başlık>>Title
      metin += "<br><a href=\" ?pin=on\"><button type='button'>ON</button></a>"; //Buton>>Button
      metin += "<br><a href=\" ?pin=off\"><button type='button'>OFF</button></a>";  //Buton>>Button
      
      String cipsend = "AT+CIPSEND=";//Komut gönderiyoruz>>We send commands
      cipsend +="0";
      cipsend +=",";
      cipsend += metin.length();
      cipsend += "\r\n";
      Serial.print(cipsend);
      delay(500);
      Serial.println(metin);
      led_yakma_servo_dondurme();
      
      Serial.println("AT+CIPCLOSE=0");//Sunucuyu kapatttık>>We closed the server
      
    }
  }
}

void led_yakma_servo_dondurme(){
 String gelen ="";
 char serialdenokunan;
 while(Serial.available()>0){
 serialdenokunan = Serial.read();
 gelen +=serialdenokunan;
 
 }
 Serial.println(gelen);
 if((gelen.indexOf(":GET /?pin=on")>1)){  //on butonuna basıldığında ve server adresinde /?pin=on var ise>>if On button is pressed and /?pin=on exists in server
  digitalWrite(role, HIGH);                 
 }
  if((gelen.indexOf(":GET /?pin=off")>1)){ // off butonuna basıldığında server adresinde /?pin=off var ise>>if off button is pressed and /?pin=off exists in server
  digitalWrite(role, LOW);;                   
 }
 
    }
