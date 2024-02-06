const int pwmPin = 9; // Define o pino PWM no qual o LED está conectado

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial com a taxa de 9600 bps
  pinMode(pwmPin, OUTPUT); // Configura o pino como saída PWM
}

void loop() {
  if (Serial.available() > 0) {
    // Lê a entrada serial como uma string até que um caractere de nova linha seja recebido
    String input = Serial.readStringUntil('\n');
    
    // Converte a string para um valor de ponto flutuante
    float tensao = input.toFloat();
    
    // Garante que a tensão esteja no intervalo de 0.00 a 5.00V
    tensao = constrain(tensao, 0.00, 5.00);
    
    // Converte a tensão para o intervalo de 0 a 255 (valor PWM)
    int valorPWM = map(tensao * 100, 0, 500, 0, 255);
    
    // Define o valor PWM no pino
    analogWrite(pwmPin, valorPWM);
    
    // Imprime o valor PWM correspondente e a tensão de 0 a 5.00V no Serial Monitor
    Serial.print("Valor PWM (0-255): ");
    Serial.println(valorPWM);
    Serial.print("Tensão (0-5.00V): ");
    Serial.print(tensao, 2); // Exibe duas casas decimais
    Serial.println(" V");
    
    // Calcula e imprime a tensão de 0 a 10.00V no Serial Monitor
    float tensao10V = map(valorPWM, 0, 255, 0, 1000) / 100.0; // Divide por 100 para obter 10.00V
    Serial.print("Tensão (0-10.00V): ");
    Serial.print(tensao10V, 2); // Exibe duas casas decimais
    Serial.println(" V");
  }
}
