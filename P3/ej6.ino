int pulsador = 7; 
int motor = 11;  
int val= 0; 

void setup() {
   pinMode(motor, OUTPUT);
   pinMode(motor, INPUT);
   digitalWrite(motor, LOW);
}


void loop() {
   val = digitalRead(pulsador);
   
   // Si esta pulsado el pulsador el motor funciona 
   if(val == HIGH) {      
      digitalWrite(motor, HIGH);
   } else {
     digitalWrite(motor, LOW);
   }
}
