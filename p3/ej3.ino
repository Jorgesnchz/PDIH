const int led1 = 13;
const int led2 = 12;
const int led3 = 11;
const int led4 = 10;

void setup(){
// Configurar los pines como salidas
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
}

void loop(){
    // De derecha a izquierda
    digitalWrite(led1, HIGH);
    delay (300);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(3000);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    delay (300);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    delay(300);
    digitalWrite(led4, LOW);

    // De izquierda a derecha
    digitalWrite(led3, HIGH);
    delay (300);
    digitalWrite(led3, LOW);
    digitalWrite(led2, HIGH);
    delay (300);
    digitalWrite(led2, LOW);
}

