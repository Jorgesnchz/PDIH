int val = 0;
const int ledRojo=11;
const int ledAmarillo=12;
const int ledVerde=13;
const int pulsador=7;

void setup()
{
	pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(pulsador, OUTPUT);

}

void loop()
{
  // Leer el valor del input
  val = digitalRead(7);  

  // Si se suelta el pulsador empieza el ciclo en el verde
  if (val == LOW) {
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarillo, LOW);
    delay(1500);
    
    digitalWrite(ledAmarillo, HIGH);
    digitalWrite(ledVerde, LOW);
    delay(1500);

  }
  // Si el pulsador esta presionado se enciende el rojo
  else {
	digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarillo, LOW);
	digitalWrite(ledRojo, HIGH);
  
	
  }
}

