#include <stdio.h>
#include "pico/stdlib.h"

#define BUZZER_PIN 15
#define STOP_BUTTON_PIN 14  // Botão para parar o alarme
#define RESET_BUTTON_PIN 13 // Botão para reiniciar o alarme
#define LED_PIN 25 // LED embutido no Pico

void iniciar_alarme() {
    gpio_put(BUZZER_PIN, 1);
    gpio_put(LED_PIN, 1); // Acende LED indicando alarme ativo
    printf("Alarme ativado!\n");

    // O alarme continua ligado até que o botão de parada seja pressionado
    while (!gpio_get(STOP_BUTTON_PIN)) {
        sleep_ms(10);
    }

    // Pequeno delay para debounce do botão STOP
    sleep_ms(50);
    while (gpio_get(STOP_BUTTON_PIN)) {
        sleep_ms(10);  //Aguarda o botão ser solto
    }

    gpio_put(BUZZER_PIN, 0);
    gpio_put(LED_PIN, 0); //Apaga LED indicando que o alarme parou
    printf("Alarme desligado! Pressione o botão de reinício para ativar novamente.\n");
}

int main() {
    stdio_init_all();

    // Inicializa os GPIOs
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0); // Garante que o buzzer inicie desligado

    gpio_init(STOP_BUTTON_PIN);
    gpio_set_dir(STOP_BUTTON_PIN, GPIO_IN);
    gpio_pull_down(STOP_BUTTON_PIN);

    gpio_init(RESET_BUTTON_PIN);
    gpio_set_dir(RESET_BUTTON_PIN, GPIO_IN);
    gpio_pull_down(RESET_BUTTON_PIN);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0); // Garante que o LED inicie apagado

    while (1) {
        // Aguarda o botão de reinício ser pressionado
        while (!gpio_get(RESET_BUTTON_PIN)) {
            sleep_ms(10);
        }

        // Espera o botão ser solto para evitar reinícios acidentais
        sleep_ms(50);
        while (gpio_get(RESET_BUTTON_PIN)) {
            sleep_ms(10);
        }

        printf("Reiniciando o alarme...\n");

        iniciar_alarme();
    }

    return 0;
}

