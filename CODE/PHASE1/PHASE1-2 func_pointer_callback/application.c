#include <stdio.h>
#include <stdint.h>

// 指针函数和回调函数
typedef struct DriverOps {
    void (*init)(void);
    void (*send)(uint8_t *data);
} DriverOps;

void usart_init(void) {
    // Initialize USART hardware
    printf("USART initialized.\n");
}

void usart_send(uint8_t *data) {
    // Send data over USART
    printf("Sending data over USART: %s\n", data);
}

void spi_init(void) {
    // Initialize SPI hardware
    printf("SPI initialized.\n");
}

void spi_send(uint8_t *data) {
    // Send data over SPI
    printf("Sending data over SPI: %s\n", data);
}

DriverOps usart_driver = {
    .init = usart_init,
    .send = usart_send
};

DriverOps spi_driver = {
    .init = spi_init,
    .send = spi_send
};

void driver_test(const DriverOps *ops)
{
    ops->init();
    uint8_t data[] = "Hello, World!";
    ops->send(data);
}


// 状态机

void idle_handler(void) {
    printf("Robot : idle\n");
}

void run_handler(void) {
    printf("Robot : run\n");
}

void stop_handler(void) {
    printf("Robot : stop\n");
}
typedef void (*UartRxCallback)(uint8_t cmd);
typedef void (*StateHandler)(void);

static UartRxCallback uart_rx_callback = NULL;

StateHandler state_handlers[] = {
    idle_handler,
    run_handler,
    stop_handler
};

void app_usart_rx_callback(uint8_t cmd)
{
    if (cmd < sizeof(state_handlers) / sizeof(state_handlers[0])) {
        state_handlers[cmd]();
    } else {
        printf("Invalid command received: %d\n", cmd);
    }
}



void uart_register_callback(UartRxCallback callback)
{
    uart_rx_callback = callback;
}


int main(void) {
    // Test USART driver
    printf("Testing USART driver:\n");
    driver_test(&usart_driver);

    // Test SPI driver
    printf("\nTesting SPI driver:\n");
    driver_test(&spi_driver);

    // Simulate receiving commands via UART
    printf("\nSimulating UART command reception:\n");
    uart_register_callback(app_usart_rx_callback);

    uart_rx_callback(0); // idle
    uart_rx_callback(1); // run
    uart_rx_callback(2); // stop
    uart_rx_callback(3); // invalid command


  printf("\nPress Enter to exit...");
    getchar();   // 等待按键

    return 0;
}
