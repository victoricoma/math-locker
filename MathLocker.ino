#include <IRremote.h>

int RECV_PIN = 11;    
int pinoledvermelho = 5;  
int pinoledverde = 7;
float eq[2][3];
String leitura="";
long x=0, y=0, a=0, b=0;

void setup()  
{  
  pinMode(pinoledvermelho, OUTPUT);   
  pinMode(pinoledverde, OUTPUT);  
  Serial.begin(9600);  
  IrReceiver.begin(RECV_PIN);
  randomSeed(analogRead(0));
}
//Função 1: para leitura dos numeros IR
int lerNumeros(){
  int saida=0;
  if(IrReceiver.decode()){
    auto dado= IrReceiver.decodedIRData.decodedRawData;
      switch(dado){
        case 4077698816:
        leitura+= "0";
        Serial.println(leitura);
        break;
        case 4010852096:
        leitura+="1";
        Serial.println(leitura);
        break;
        case 3994140416:
        leitura+="2";
        Serial.println(leitura);
        break;
        case 3977428736:
        leitura+="3";
        Serial.print(leitura);
        break;
        case 3944005376:
        leitura+="4";
        Serial.println(leitura);
        break;
        case 3927293696:
        leitura+="5";
        Serial.println(leitura);
        break;
        case 3910582016:
        leitura+="6";
        Serial.println(leitura);
        break;
        case 3877158656:
        leitura+="7";
        Serial.println(leitura);
        break;
        case 3860446976 :
        leitura+="8";
        Serial.println(leitura);
        break;
        case 3843735296:
        leitura+="9";
        Serial.println(leitura);
        case 4194680576:
        saida = converteNumero(leitura);
        leitura="";
        break;
    }
    IrReceiver.resume();
  }
  delay(500);
  return saida;
}
//Função 2: de converter em numero
int converteNumero(String teclado){
  return teclado.toInt();
}
//Função 3: Irá ler os números da Matriz
void lerMatriz(float numero){
  for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){
      eq[i][j]=numero;
    }
  }
}
//Função 4: Irá exibir a Matriz da Equacao
void exibirMatriz(){
  Serial.print(eq[0][0]);
  Serial.print("x");
  Serial.print(" + ");
  Serial.print(eq[0][1]);
  Serial.print("y");
  Serial.print(" = ");
  Serial.println(eq[0][2]);
  Serial.print(eq[1][0]);
  Serial.print("x");
  Serial.print(" + ");
  Serial.print(eq[1][1]);
  Serial.print("y");
  Serial.print(" = ");
  Serial.println(eq[1][2]);
}
//Função5: Resolve a Equacao
void resolveEquacao(){
  eq[0][1]=((eq[1][0]*eq[0][2])-eq[1][2])/((eq[1][0]*eq[0][0])-eq[1][1]);
  eq[0][0]=(eq[0][2]-eq[0][1]);
  exibirMatriz();
}
//Função 6: Monta a Matriz da Equação
void faseUm(long x, long y){
  a=random(1,10);
  b=random(1,10);
  eq[0][0]=1;
  eq[0][1]=1;
  eq[0][2]=(x+y);
  eq[1][0]=(a);
  eq[1][1]=(b);
  eq[1][2]=((a*x)+(b*y));
  exibirMatriz();
}
void loop(){
  
}
