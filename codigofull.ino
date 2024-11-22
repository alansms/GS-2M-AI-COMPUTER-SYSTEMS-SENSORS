#include <WiFi.h>
#include <PubSubClient.h>

// Configurações de rede Wi-Fi
const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA_WIFI";

// Configurações do MQTT
const char* mqtt_server = "SEU_SERVIDOR_MQTT";
const int mqtt_port = 1883; // Porta padrão MQTT
const char* mqtt_user = "SEU_USUARIO_MQTT";
const char* mqtt_password = "SUA_SENHA_MQTT";
const char* topic_status = "esp32/status";
const char* topic_relay1 = "esp32/relay1";

WiFiClient espClient;
PubSubClient client(espClient);

#define BUTTON_PIN 40     // Botão 01
#define RELAY1_PIN 38     // Rele-01
#define RELAY2_PIN 39     // Rele-02
#define PIR_SENSOR_PIN 37 // Sensor PIR

unsigned long lastMotionTime = 0;
unsigned long lastCheckTime = 0;
const unsigned long checkInterval = 10 * 60 * 1000; // 10 minutos
const unsigned long countdownInterval = 1000; // Atualização do tempo restante (1 segundo)

bool relay1State = false; // Estado do Rele-01
bool lastButtonState = HIGH;
unsigned long timeRemaining = checkInterval;

// Função para conectar ao Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se ao Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

// Função para reconectar ao MQTT caso desconecte
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("Conectado!");
      client.publish(topic_status, "ESP32 conectado ao servidor MQTT!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  // Configuração dos pinos
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(PIR_SENSOR_PIN, INPUT);

  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, HIGH); // Rele-02 sempre ligado

  Serial.begin(115200);
  Serial.println("Iniciando...");

  setup_wifi(); // Conecta ao Wi-Fi
  client.setServer(mqtt_server, mqtt_port); // Configura o servidor MQTT

  Serial.println("Sistema iniciado!");
}

void loop() {
  if (!client.connected()) {
    reconnect(); // Reconecta ao MQTT se necessário
  }
  client.loop();

  unsigned long currentTime = millis();

  // Leitura do botão
  bool currentButtonState = digitalRead(BUTTON_PIN);
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    relay1State = !relay1State;
    digitalWrite(RELAY1_PIN, relay1State ? HIGH : LOW);
    Serial.print("Rele-01 ");
    Serial.println(relay1State ? "ligado!" : "desligado!");

    // Publica o estado do Rele-01 no MQTT
    client.publish(topic_relay1, relay1State ? "ligado" : "desligado");

    if (relay1State) {
      lastMotionTime = currentTime;
      timeRemaining = checkInterval;
    }
  }
  lastButtonState = currentButtonState;

  // Leitura do sensor PIR
  bool pirState = digitalRead(PIR_SENSOR_PIN);
  if (pirState == HIGH) {
    lastMotionTime = currentTime;
    timeRemaining = checkInterval;

    if (!relay1State) {
      relay1State = true;
      digitalWrite(RELAY1_PIN, HIGH);
      Serial.println("Rele-01 ligado pelo sensor PIR!");
      client.publish(topic_relay1, "ligado pelo PIR");
    }
  }

  // Atualiza a contagem regressiva
  if (relay1State) {
    timeRemaining = checkInterval - (currentTime - lastMotionTime);
    unsigned long secondsRemaining = timeRemaining / 1000;

    if (currentTime - lastCheckTime >= countdownInterval) {
      lastCheckTime = currentTime;
      Serial.print("Tempo restante para desligar o Rele-01: ");
      Serial.print(secondsRemaining);
      Serial.println(" segundos");

      // Publica o tempo restante no MQTT
      char msg[50];
      snprintf(msg, 50, "Tempo restante: %lu segundos", secondsRemaining);
      client.publish(topic_status, msg);
    }

    if (timeRemaining <= 0) {
      relay1State = false;
      digitalWrite(RELAY1_PIN, LOW);
      Serial.println("Rele-01 desligado por inatividade!");
      client.publish(topic_relay1, "desligado por inatividade");
    }
  }

  digitalWrite(RELAY2_PIN, HIGH); // Rele-02 sempre ligado

  delay(100);
}
