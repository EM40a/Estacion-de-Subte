#define BUZZER 14 //A0
#define PULSADOR 13 
#define CONSTITUCION 12
#define SAN_JUAN 11
#define INDEPENDENCIA 10
#define MORENO 9
//Cada letra representa una luz del diplay 7 segmentos
#define a 8
#define b 7
#define c 6
#define d 5
#define e 4
#define f 2
#define g 3
//La funcion apaga o prende cada pin del display segun el parametro recibido
void ApagarPrender7Segmentos(int apagarPrender){
  //Un array con cada pin del display
  int segmentos[] = {a, b, c, d, e, f, g};
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentos[i], apagarPrender);
  }
} 

void NumeroUno() {
  ApagarPrender7Segmentos(LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}

void NumeroDos(){
  ApagarPrender7Segmentos(HIGH);
  digitalWrite(c, LOW);
  digitalWrite(f, LOW);
}

void NumeroTres() {
  ApagarPrender7Segmentos(HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
}

void CuentaRegresiva(int numero) {
  switch (numero) {
    case 3:
      NumeroTres();
      break;
    case 2:
      NumeroDos();
      break;
    case 1:
      NumeroUno();
      break;
  }
}

void CambioDeEstacion(int estacion, int numero, int frecuencia) 
{
  digitalWrite(estacion, HIGH);
  CuentaRegresiva(numero);
  tone(BUZZER, frecuencia, 1000);
  delay(1000);
  digitalWrite(estacion, LOW);
  ApagarPrender7Segmentos(LOW);
  delay(1000);
}

void ImprimirProximaEstacion(String estacion)
{
  Serial.println("Proxima estacion: " + estacion);
}

void setup()
{
  for (int i = 2; i < 15; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(PULSADOR, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  while(digitalRead(PULSADOR) == LOW) //Cuando presione el pulsador
  {
    ImprimirProximaEstacion("San Juan");
    CambioDeEstacion(CONSTITUCION, 3, 100);

    ImprimirProximaEstacion("Indepencia");
    CambioDeEstacion(SAN_JUAN, 2, 150);
    
    ImprimirProximaEstacion("Moreno");
    CambioDeEstacion(INDEPENDENCIA, 1, 200);
    
    ImprimirProximaEstacion("Indepencia");
    CambioDeEstacion(MORENO, 3, 250);
    
    ImprimirProximaEstacion("San Juan");
    CambioDeEstacion(INDEPENDENCIA, 2, 200);
    
    ImprimirProximaEstacion("Constitucion");
    CambioDeEstacion(SAN_JUAN, 1, 150);
   }
}