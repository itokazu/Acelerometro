#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

void setup()
{
  pinMode(32,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);

  Serial.begin(115200);

  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  Serial.println("sensor MPU-6050 encontrado");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; 
  }
  display.display();
  delay(500); // Pause for 2 seconds
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);

}

void loop()
{
  digitalWrite(32, LOW); //buzzer
  digitalWrite(15, LOW); //LED VERMELHO
  digitalWrite(2, LOW); //LED AMARERO
  digitalWrite(4, LOW); //LED VERDE
  
  sensors_event_t g, a, temp;
  mpu.getEvent(&g, &a, &temp);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Giroscopio - rps");
  display.print(g.gyro.x, 1);
  display.print(", ");
  display.print(g.gyro.y, 1);
  display.print(", ");
  display.print(g.gyro.z, 1);
  display.println("");
  display.println("");
  
  display.println("Acelerometro - m/s^2");
  display.print(a.acceleration.x, 1);
  display.print(", ");
  display.print(a.acceleration.y, 1);
  display.print(", ");
  display.print(a.acceleration.z, 1);
  display.println("");
  display.println("");  

  display.println("Temperatura");
  display.print(temp.temperature, 1);
 
  display.display();
  delay(100);
  
  if (g.gyro.x > 8) {
    digitalWrite(32, HIGH);
    delay(100);
    digitalWrite(32, LOW);
    digitalWrite(15, HIGH);
    delay(500);
    digitalWrite(15, LOW);
  }

  if (g.gyro.y > 8) {
    digitalWrite(32, HIGH);
    delay(100);
    digitalWrite(32, LOW);
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
  }
  
  if (g.gyro.z <= 0 ) {
    digitalWrite(32, HIGH);
    delay(100);
    digitalWrite(32, LOW);
    digitalWrite(4, HIGH);
    delay(500);
    digitalWrite(4, LOW);
  }
}