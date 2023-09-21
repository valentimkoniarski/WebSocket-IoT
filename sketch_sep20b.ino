#include <WiFi.h>
#include <WebSocketsServer.h>

// Defina as credenciais da rede WiFi
const char* ssid = ".";
const char* password = "!abc.269";


// Crie uma instância do servidor WebSocket na porta 81
WebSocketsServer webSocket = WebSocketsServer(81);

void setup() {
  Serial.begin(115200);

  // Conecte-se à rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
    Serial.println(WiFi.status());
    Serial.println(WiFi.localIP());
  }
  Serial.println("Conectado ao WiFi");

  // Inicialize o servidor WebSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  // Manipule eventos WebSocket
  webSocket.loop();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    // Quando um cliente se conecta
    case WStype_CONNECTED:
      Serial.printf("Cliente #%u conectado\n", num);
      break;
    
    // Quando um cliente envia uma mensagem
    case WStype_TEXT:
      Serial.printf("Recebido de #%u: %s\n", num, payload);
      
      // Transmita a mensagem de volta para todos os clientes conectados
      webSocket.broadcastTXT(payload, length);
      break;
    
    // Quando um cliente se desconecta
    case WStype_DISCONNECTED:
      Serial.printf("Cliente #%u desconectado\n", num);
      break;
  }
}
