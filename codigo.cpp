#include <LiquidCrystal.h>

// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


// Variáveis

int Proximasenha=1;
int Senhaatual=1;
int totalpessoas = 0;


//formatar senha
String formatarSenha(int numero) {
  String senha = "S";
  
  if (numero < 10) {
    senha += "00";
  } 
  else if (numero < 100) {
    senha += "0";
  }
  
  senha += String(numero);
  return senha;
  }



 void setup() {
  Serial.begin(9600);  // Inicia Monitor Serial
  lcd.begin(16, 2);    // Inicia LCD 16x2
  
  lcd.clear();
   
  lcd.setCursor(0, 0);
  lcd.print("Sistema Senhas");
                       
  Serial.println("--Sistema de fila--");
  Serial.println("comandos:");
  Serial.println("G-Gerar senha:");
  Serial.println("C-chamar proximo senha:");
  Serial.println("F-Consultar fila:");
  Serial.println("R - Reiniciar sistema");
   
   
  delay(2000);
  mostrarMenu(); 
}

void loop() {
  // O loop deve ficar aqui em cima, cuidando da leitura das letras
  if (Serial.available() > 0) {
    char comando = Serial.read();
    
    if (comando == '\n' || comando == '\r') return;

    switch (comando) {
      case 'g': case 'G': gerarSenha(); break;
      case 'c': case 'C': chamarProximo(); break;
      case 'f': case 'F': consultarFila(); break;
      case 'r': case 'R': reiniciarSistema(); break;
      default:
        Serial.println("Comando invalido!");
        break;
    }
    delay(500); // Pequena pausa para evitar leituras duplas
  }
 }



// A função mostrarMenu deve ficar FORA das outras
void mostrarMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("G:Ger C:Cham"); // Reduzi o texto para caber nos 16 espaços
  lcd.setCursor(0, 1);       // Cursor na segunda linha (0, 1)
  lcd.print("F:Fila R:Reset");
  
  Serial.println("\nDigite um comando:");
}



void gerarSenha() {

  String senhaFormatada = formatarSenha(Proximasenha);

  Serial.print("Sucesso! Senha gerada: ");
  Serial.println(senhaFormatada);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Senha Gerada:");
  lcd.setCursor(0, 1);
  lcd.print(senhaFormatada);


  Proximasenha++; 
  totalpessoas++;  
  
  delay(3000);
  mostrarMenu();
}

void chamarProximo(){
  

  if(totalpessoas == 0) {
    lcd.clear();
    lcd.print("Fila vazia");
    Serial.println("Fila vazia");
    
    
  } else {
   String senhaChamando = formatarSenha(Senhaatual);
    Serial.println("Chamando " + senhaChamando);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("chamando: ");
    lcd.setCursor(0,1);
    lcd.print(senhaChamando);
    
    Senhaatual++;
    totalpessoas--;
    
  
  }
	delay(3000);
  	mostrarMenu();
}

void consultarFila() {
 Serial.println("<= STATUS =>");
  
  if (totalpessoas == 0) {
    Serial.println("Proxima senha:Nao tem pessoas na fila");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Proxima senha:");
    lcd.setCursor(0,1);
    
    lcd.print("Fila Vazia.");
    
  }else{
    Serial.print("Proximo senha: ");
    Serial.println(formatarSenha(Senhaatual));
    
   Serial.print("total de pessoas na fila: ");
    Serial.println(totalpessoas);
    lcd.setCursor(0,1);
    
  } 

  delay(2000);
  mostrarMenu();
}
void reiniciarSistema() {
  Proximasenha = 1;
  Senhaatual = 1;
  totalpessoas = 0;
    
  Serial.println("Sistema reiniciado");  
  Serial.println("Fila vazia");
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sistema");
  lcd.setCursor(0,1);
  lcd.print("Reiniciado");
  
  Serial.println("Sistema reiniciado!");
  Serial.println("Senhas reiniciadas para S001");
  
  delay(3000);
  mostrarMenu();
}