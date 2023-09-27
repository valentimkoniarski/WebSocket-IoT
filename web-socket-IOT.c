#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// TODO Definir credenciais da rede WiFi
const char* ssid = ".";
const char* password = "!abc.269";

#define MAX_MESSAGES 50

String messages[MAX_MESSAGES];
int messageCount = 0;

WebSocketsServer webSocket = WebSocketsServer(81);
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");
  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  server.on("/mensagens-historico", HTTP_GET, [](AsyncWebServerRequest *request){
    // Criar um objeto JSON para armazenar o histórico de mensagens
    DynamicJsonDocument jsonDocument(1024); // Tamanho do buffer JSON
    JsonArray jsonArray = jsonDocument.to<JsonArray>();

    // Adicionar mensagens salvas ao objeto JSON
    for (int i = 0; i < messageCount; i++) {
      jsonArray.add(messages[i]);
    }

    // Converter o objeto JSON em uma string
    String jsonStr;
    serializeJson(jsonDocument, jsonStr);

    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", jsonStr);
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
  });
  server.begin();
}

void loop() {
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
