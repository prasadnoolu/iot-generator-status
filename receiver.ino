#include <SoftwareSerial.h>
#include<ESP8266WiFi.h>
#include<PubSubClient.h>

#define CLIENT_ID "GenGateway" 

const char* ssid = "sandeep"; // change to your home wifi name
const char* password = "22122012"; //  change to your home wifi password
const char* mqtt_server = "210.212.210.86";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

SoftwareSerial s(D1,D2);
String data;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}




void setup() {
s.begin(9600);
Serial.begin(9600);
setup_wifi();

  client.setServer(mqtt_server, 1883);
}
 
void loop() {
  //s.write("s");
  String gen;
  char mesg[30];
  if (s.available()>0)
  {
    data=s.readString();
    Serial.println(data);
  }
  if(data.length()>10)
  {
    String id=data.substring(0,2);
    String ontime=data.substring(3,11);
    String offtime=data.substring(11,19);
    Serial.println(id);
    Serial.println(ontime);
    Serial.println(offtime);
    gen=id+"/"+ontime+"/"+offtime;
    gen.toCharArray(mesg,30);
    if (client.connect(CLIENT_ID)){

      Serial.println("sending message to the mobile app");
      client.publish("generator",mesg);
      data="";

  }
    }
 
 
}
