// *===== BIBLIOTECAS ======
#include <Arduino.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "entradas.h"
#include "atuadores.h"
#include <Stepper.h>

#define mqtt_pub_topic1 "projetoKaue/AutoFactory/Esteiraa"

void acao_botao_externo();

unsigned long tempo_anterior = 0;
const unsigned long intervalo = 1000;

const int stepsPerRevolution = 2048; // é o número de passos que um motor de passo deve dar para completar uma volta completa de 360 graus.

void setup()
{
  Serial.begin(115200);
  inicializa_motor();
}

void loop()
{
  rotacao_motor();
  
  String json;
  JsonDocument doc;
  bool mensagemEmFila = false;
  if (millis() - tempo_anterior >= intervalo)
  {
    tempo_anterior = millis();
    doc["EsteiraState"] = rotacao_motor();
    mensagemEmFila = true;
  }
  if (botao_externo_pressionado())
  {
    doc["BotaoState"] = true;
    doc["EsteiraState"] = rotacao_motor();
    mensagemEmFila = true;
  }
  else if (botao_externo_solto())
  {
    doc["BotaoState"] = false;
    doc["EsteiraState"] = rotacao_motor();
    mensagemEmFila = true;
  }
  if (mensagemEmFila)
  {
    serializeJson(doc, json);
    publica_mqtt(mqtt_pub_topic1, json);
    mensagemEmFila = false;
  }
}