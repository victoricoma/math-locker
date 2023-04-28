#include <LiquidCrystal.h>
#include <IRremote.h>
#include <Servo.h>

Servo tranca_6;
int RECV_PIN = 11;
float eq[2][3];
float teste = 523.56325;
String leitura = "", l1 = "", l2 = "";
long x = 0, y = 0, a = 0, b = 0, n1 = 0, n2 = 0;
bool f = false;
const int rs = 3, en = 4, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  IrReceiver.begin(RECV_PIN);
  randomSeed(analogRead(0));
}
//Função 1: para leitura dos numeros IR
void lerNumeros() {
  if (IrReceiver.decode()) {
    auto dado = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(dado);
    if (f == false) {
      tranca_6.write(0);
      f = true;
      n1 = random(1, 10);
      n2 = random(1, 10);
      faseUm(n1, n2);
      exibirLcd("Aperte EQ!", "...");
      delay(1000);
      exibirLcd(l1, l2);
    }
    delay(500);
    switch (dado) {
      case 3860463360:
        leitura += "0";
        break;
      case 3125149440:
        leitura += "1";
        break;
      case 3108437760:
        leitura += "2";
        break;
      case 3091726080:
        leitura += "3";
        break;
      case 3141861120:
        leitura += "4";
        break;
      case 3208707840:
        leitura += "5";
        break;
      case 3158572800:
        leitura += "6";
        break;
      case 4161273600:
        leitura += "7";
        break;
      case 3927310080 :
        leitura += "8";
        break;
      case 4127850240:
        leitura += "9";
        break;
      case 3810328320:
        exibirLcd("Digitou: ", leitura);
        exibirLcd("X << ou >> Y", "---escolha---");
        break;
      case 4144561920:
        x = converteNumero(leitura);
        exibirLcd("Adicionado>>X:", leitura);
        leitura = "";
        break;
      case 2774204160:
        y = converteNumero(leitura);
        exibirLcd("Adicionado>>Y:", leitura);
        leitura = "";
        break;
      case 4061003520:
        exibirLcd("[Play] X e Y", "[UP] Resposta");
        break;
      case 3877175040:
        resolveEquacao();
        delay(1500);
        if (y == eq[0][1] && x == eq[0][0]) {
          exibirLcd("Acertou", "Miseravel!!");
          tranca_6.write(90);
        } else {
          exibirLcd("Errouuu...", "Errourude!!");
        }
        break;
    }
    IrReceiver.resume();
    delay(500);
  }
}
//Função 2: de converter em numero
int converteNumero(String teclado) {
  return teclado.toInt();
}
//Função 4: Irá exibir a Matriz da Equacao
void exibirMatriz(){
  l1+=String(eq[0][0],0);
  l1+="x+";
  l1+=String(eq[0][1],0);
  l1+="y=";
  l1+=String(eq[0][2],0);
  l2+=String(eq[1][0],0);
  l2+="x+";
  l2+=String(eq[1][1],0);
  l2+="y=";
  l2+=String(eq[1][2],0);
}
//Função5: Resolve a Equacao
void resolveEquacao() {
  eq[0][1] = ((eq[1][0] * eq[0][2]) - eq[1][2]) / ((eq[1][0] * eq[0][0]) - eq[1][1]);
  eq[0][0] = (eq[0][2] - eq[0][1]);
  exibirMatriz();
}
//Função 6: Monta a Matriz da Equação
void faseUm(long x, long y) {
  a = random(1, 10);
  b = random(1, 10);
  eq[0][0] = 1;
  eq[0][1] = 1;
  eq[0][2] = (x + y);
  eq[1][0] = (a);
  eq[1][1] = (b);
  eq[1][2] = ((a * x) + (b * y));
  exibirMatriz();
}
void exibirLcd(String l1, String l2){
  if(l1 && l2){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(l1);
    lcd.setCursor(0,1);
    lcd.print(l2);
  }
}
void loop() {
  lerNumeros();
}
