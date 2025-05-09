const int ultra= 9;
const int echo = 10;
const int buzzer = 8;

void setup() {
  pinMode(ultra, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  long duration;
  int distance;

  digitalWrite(ultra, LOW);
  delayMicroseconds(2);
  digitalWrite(ultra, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultra, LOW);


  duration = pulseIn(echo, HIGH);

  // Calcular distancia en cm
  distance = duration * 0.034 / 2;

 // Si está a menos de 5 cm suena
  if (distance < 5 && distance > 0) {
    tone(buzzer, 1000);
  } else {
    noTone(buzzer);
  }


  // Se ejecuta una vez cada segundo
  delay(1000);
}
