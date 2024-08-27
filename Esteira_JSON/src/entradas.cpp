#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"

//Definição dos pinos dos botões
#define BOTAO_EXTERNO_PIN 12

//Criação dos objetos para debouncing
Bounce botaoExterno = Bounce();

//Inicializa as entradas digitais
void inicializa_entradas()
{
    botaoExterno.attach(BOTAO_EXTERNO_PIN, INPUT_PULLUP);
}

//Atualiza o estado dos botões
void atualiza_botoes()
{
    //atualiza do estado do botao_boot
    botaoExterno.update();
}

//Retorna se o botão externo foi pressionado
bool botao_externo_pressionado()
{
    return botaoExterno.fell();
}

bool botao_externo_solto()
{
    return botaoExterno.rose();
}