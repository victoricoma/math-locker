#include <IRremote.hpp>

int RECV_PIN = 11;    
int pinoledvermelho = 5;  
int pinoledverde = 7;
float eq[2][3];
String leitura="";
long x=0, y=0, a=0, b=0, n1=0, n2=0;
bool f=false;

void setup()  
{  
  pinMode(pinoledvermelho, OUTPUT);   
  pinMode(pinoledverde, OUTPUT);  
  Serial.begin(9600);  
  IrReceiver.begin(RECV_PIN);
  randomSeed(analogRead(0));
}
//Função 1: para leitura dos numeros IR
void lerNumeros(){
  if(IrReceiver.decode()){
    auto dado= IrReceiver.decodedIRData.decodedRawData;
    Serial.println(dado);
    if(f==false){
      f=true;
      Serial.println("Aperte *!");
      delay(1000);
      Serial.println("Gerando Equação...");
    }
    delay(500);
    switch(dado){
        case 3860463360:
        leitura+= "0";
        break;
        case 3125149440:
        leitura+="1";
        break;
        case 3108437760:
        leitura+="2";
        break;
        case 3091726080:
        leitura+="3";
        break;
        case 3141861120:
        leitura+="4";
        break;
        case 3208707840:
        leitura+="5";
        break;
        case 3158572800:
        leitura+="6";
        break;
        case 4161273600:
        leitura+="7";
        break;
        case 3927310080 :
        leitura+="8";
        break;
        case 4127850240:
        leitura+="9";
        case 3810328320:
        Serial.print("Digitou: ");
        Serial.println(leitura);
        Serial.println("X << ou >> Y");
        break;
        case 4144561920:
        Serial.print("Adicionado >> x= ");
        x=converteNumero(leitura);
        Serial.println(x);
        leitura="";
        break;
        case 2774204160:
        Serial.print("Adicionado >> y= ");
        y=converteNumero(leitura);
        Serial.println(y);
        leitura="";
        break;
        case 4061003520:
        n1=random(1,10);
        n2=random(1,10);
        faseUm(n1, n2);
        Serial.println("[OK] X e Y");
        Serial.println("[UP] Resposta");
        break;
        case 3877175040:
        resolveEquacao();
      if(x==eq[0][1] && y==eq[0][0]){
        Serial.println("Acertou Miseravel");
      }else{
        Serial.println("Errouuuuuu!");
      }
        break;
    }
    IrReceiver.resume();
    delay(500);
  }
}
//Função 2: de converter em numero
int converteNumero(String teclado){
  return teclado.toInt();
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
  lerNumeros();
}
