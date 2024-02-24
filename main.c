#include <stdint.h>

// Definiciones de direcciones de registros
#define RCC 0X40021000U // DECLARA A LOS REGISTROS DEL RELOJ
#define RCC_IOPEN (RCC + 0X0000002CU) // PARA HABILITAR LOS PUERTOS DEL RELOJ

#define PORTA 0x50000000U // DECLARA EL PUERTO A
#define PORTA_MODE (PORTA + 0X00000000U) // DECLARA EL MODO QUE TOMARA EL PIN DEL PUERTO A
#define PORTA_ODR (PORTA + 0X00000014U)   // REGISTRO PARA MANDAR UN 0 O 1 A LA SALIDA DEL PUERTO A

#define PORTB 0X50000400U // DECLARA EL PUERTO B
#define PORTB_MODE (PORTB + 0X00000000U) // DECLARA EL MODO QUE TOMARA EL PIN DEL PUERTO B
#define PORTB_IDR (PORTB + 0X00000010U)   // REGISTRO PARA LEER UN 0 O 1 A LA SALIDA DEL PUERTO B
#define PORTB_PULL (PORTB + 0X0000000CU)

#define PORTC 0X50000800U // DECLARAR EL PUERTO C
#define PORTC_MODE (PORTC + 0X00000000U) // DECLARA EL MODO QUE TOMARA EL PIN DEL PUERTO C
#define PORTC_IDR (PORTC + 0X00000010U)   // REGISTRO PARA LEER UN 0 O 1 A LA SALIDA DEL PUERTO C
#define PORTC_PULL (PORTC + 0X0000000CU)  // DECLARA EL REGISTRO PARA PONER PULL-DOWN EN LOS PINES DEL PUERTO C

void delay_ms(uint16_t n);

int main(void)
{
    // Declarando punteros de los registros
    uint32_t *ptr_rcc_iopenr = RCC_IOPEN;

    uint32_t *ptr_porta_mode = PORTA_MODE;
    uint32_t *ptr_porta_odr = PORTA_ODR;

    uint32_t *ptr_portb_mode = PORTB_MODE;
    uint32_t *ptr_portb_idr = PORTB_IDR;
    uint32_t *ptr_portb_pulldown = PORTB_PULL;

    uint32_t *ptr_portc_mode = PORTC_MODE;
    uint32_t *ptr_portc_idr = PORTC_IDR;
    uint32_t *ptr_portc_pulldown = PORTC_PULL;

    // Configuraciones del puerto A
    *ptr_rcc_iopenr |= 1 << 0;
    *ptr_porta_mode |= 1 << 0;
    *ptr_porta_mode &= ~(1 << 1);

    // Configuraciones del puerto B
    *ptr_rcc_iopenr |= 1 << 1;
    *ptr_portb_mode &= ~(1 << 0);
    *ptr_portb_mode &= ~(1 << 1);
    *ptr_portb_pulldown &= ~(1 << 0);
    *ptr_portb_pulldown |= 1 << 1;

    // Configuraciones del puerto C
    *ptr_rcc_iopenr |= 1 << 2;
    *ptr_portc_mode &= ~(1 << 0);
    *ptr_portc_mode &= ~(1 << 1);
    *ptr_portc_pulldown &= ~(1 << 0);
    *ptr_portc_pulldown |= 1 << 1;

    uint8_t contador = 0; // Inicializa el contador

    while (1)
    {
        // Verifica si el botón B1 (pin 0 de PORTB) está presionado o no
        if (*ptr_portb_idr & (1 << 0))
        {
            // Parpadea el LED (pin 0 de PORTA) si el botón B1 no está presionado
            *ptr_porta_odr &= ~(1 << 0);
            delay_ms(500);
            *ptr_porta_odr |= 1 << 0;
            delay_ms(500);
        }
        else
        {
            // Parpadea el LED más rápido si el botón B1 está presionado
            *ptr_porta_odr &= ~(1 << 0);
            delay_ms(200);
            *ptr_porta_odr |= 1 << 0;
            delay_ms(200);
        }

        // Verifica si el botón B2 (pin 0 de PORTC) está presionado o no
        if (*ptr_portc_idr & (1 << 0))
        {
            // Incrementa el contador y espera un tiempo antes de leerlo nuevamente
            contador++;
            delay_ms(200);
        }
    }
}

void delay_ms(uint16_t n)
{
    uint16_t i;
    // Espera durante un tiempo aproximado
    for (; n > 0; n--)
        for (i = 0; i < 140; i++);
}
