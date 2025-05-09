const int ledRojo=11;
const int ledAmarillo=12;
const int ledVerde=13;

void setup() {

//Configurar los pines como salidas
pinMode(ledRojo, OUTPUT);
pinMode(ledAmarillo, OUTPUT);
pinMode(ledVerde,OUTPUT);

}

void loop() {
    //Encender el LED rojo, apagar los otros
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledVerde, LOW);
    delay(1500); 

    //Encender el LED amarillo, apagar los otros
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAmarillo, HIGH);
    digitalWrite(ledVerde, LOW);
    delay(1500); 

    //Encender el LED verde, apagar los otros
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledVerde, HIGH);
    delay(1500); 

}
