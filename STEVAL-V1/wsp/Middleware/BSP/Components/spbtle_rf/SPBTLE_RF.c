/**
 * @file       SPBTLE_RF.c
 * @brief
 * @date       2026/05/27
 * @author     [Gentantun] (nguyenthanhtung8196@gmail.com)
 * @details
 * @ref
 * @copyright  Copyright (c) 2026 RoboTun
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "SPBTLE_RF.h"
#include "gp_timer.h"
#include "debug.h"
#include "hci.h"

#include "steval_board_1.h"
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/

#ifdef PRINT_CSV_FORMAT
extern volatile uint32_t ms_counter;
#endif /* PRINT_CSV_FORMAT */
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/
#define HEADER_SIZE 5
#define MAX_BUFFER_SIZE 255
#define TIMEOUT_DURATION 15

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
SPI_HandleTypeDef SpiHandle;

/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
static void us150Delay(void);
void set_irq_as_output(void);
void set_irq_as_input(void);

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

#ifdef PRINT_CSV_FORMAT
/**
 * @brief  This function is a utility to print the log time
 *          in the format HH:MM:SS:MSS (DK GUI time format)
 * @param  None
 * @retval None
 */
void print_csv_time(void)
{
    uint32_t ms = ms_counter;
    PRINT_CSV("%02d:%02d:%02d.%03d", ms / (60 * 60 * 1000) % 24, ms / (60 * 1000) % 60, (ms / 1000) % 60, ms % 1000);
}
#endif /* PRINT_CSV_FORMAT */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin)
    {
    case BNRG_SPI_EXTI_PIN:
        HCI_Isr();
        HCI_ProcessEvent = 1;
        break;
    }
}

void Hal_Write_Serial(const void *data1, const void *data2, int32_t n_bytes1,
                      int32_t n_bytes2)
{
    struct timer t;

    Timer_Set(&t, CLOCK_SECOND / 10);

#ifdef PRINT_CSV_FORMAT
    print_csv_time();
    for (int i = 0; i < n_bytes1; i++)
    {
        PRINT_CSV(" %02x", ((uint8_t *)data1)[i]);
    }
    for (int i = 0; i < n_bytes2; i++)
    {
        PRINT_CSV(" %02x", ((uint8_t *)data2)[i]);
    }
    PRINT_CSV("\n");
#endif

    while (1)
    {
        if (BlueNRG_SPI_Write(&SpiHandle, (uint8_t *)data1, (uint8_t *)data2, n_bytes1, n_bytes2) == 0)
            break;
        if (Timer_Expired(&t))
        {
            break;
        }
    }
}

void BNRG_SPI_Init(void)
{
    SpiHandle.Instance = BNRG_SPI_INSTANCE;
    SpiHandle.Init.Mode = BNRG_SPI_MODE;
    SpiHandle.Init.Direction = BNRG_SPI_DIRECTION;
    SpiHandle.Init.DataSize = BNRG_SPI_DATASIZE;
    SpiHandle.Init.CLKPolarity = BNRG_SPI_CLKPOLARITY;
    SpiHandle.Init.CLKPhase = BNRG_SPI_CLKPHASE;
    SpiHandle.Init.NSS = BNRG_SPI_NSS;
    SpiHandle.Init.FirstBit = BNRG_SPI_FIRSTBIT;
    SpiHandle.Init.TIMode = BNRG_SPI_TIMODE;
    SpiHandle.Init.CRCPolynomial = BNRG_SPI_CRCPOLYNOMIAL;
    SpiHandle.Init.BaudRatePrescaler = BNRG_SPI_BAUDRATEPRESCALER;
    SpiHandle.Init.CRCCalculation = BNRG_SPI_CRCCALCULATION;

    HAL_SPI_Init(&SpiHandle);
}

void BlueNRG_RST(void)
{
    HAL_GPIO_WritePin(BNRG_SPI_RESET_PORT, BNRG_SPI_RESET_PIN, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(BNRG_SPI_RESET_PORT, BNRG_SPI_RESET_PIN, GPIO_PIN_SET);
    HAL_Delay(5);
}

uint8_t BlueNRG_DataPresent(void)
{
    if (HAL_GPIO_ReadPin(BNRG_SPI_EXTI_PORT, BNRG_SPI_EXTI_PIN) == GPIO_PIN_SET)
        return 1;
    else
        return 0;
}

void BlueNRG_HW_Bootloader(void)
{
    Disable_SPI_IRQ();
    set_irq_as_output();
    BlueNRG_RST();
    set_irq_as_input();
    Enable_SPI_IRQ();
}

int32_t BlueNRG_SPI_Read_All(SPI_HandleTypeDef *hspi, uint8_t *buffer,
                             uint8_t buff_size)
{
    uint16_t byte_count;
    uint8_t len = 0;
    uint8_t char_ff = 0xff;
    volatile uint8_t read_char;

    uint8_t header_master[HEADER_SIZE] = {0x0b, 0x00, 0x00, 0x00, 0x00};
    uint8_t header_slave[HEADER_SIZE];

    /* CS reset */
    HAL_GPIO_WritePin(BNRG_SPI_CS_PORT, BNRG_SPI_CS_PIN, GPIO_PIN_RESET);

    /* Read the header */
    HAL_SPI_TransmitReceive(hspi, header_master, header_slave, HEADER_SIZE, TIMEOUT_DURATION);

    if (header_slave[0] == 0x02)
    {
        /* device is ready */
        byte_count = (header_slave[4] << 8) | header_slave[3];
        if (byte_count > 0)
        {

            /* avoid to read more data that size of the buffer */
            if (byte_count > buff_size)
            {
                byte_count = buff_size;
            }

            for (len = 0; len < byte_count; len++)
            {
                __disable_irq();
                HAL_SPI_TransmitReceive(hspi, &char_ff, (uint8_t *)&read_char, 1, TIMEOUT_DURATION);
                __enable_irq();
                buffer[len] = read_char;
            }
        }
    }
    /* Release CS line */
    HAL_GPIO_WritePin(BNRG_SPI_CS_PORT, BNRG_SPI_CS_PIN, GPIO_PIN_SET);

    // Add a small delay to give time to the BlueNRG to set the IRQ pin low
    // to avoid a useless SPI read at the end of the transaction
    for (volatile int i = 0; i < 2; i++)
        __NOP();

#ifdef PRINT_CSV_FORMAT
    if (len > 0)
    {
        print_csv_time();
        for (int i = 0; i < len; i++)
        {
            PRINT_CSV(" %02x", buffer[i]);
        }
        PRINT_CSV("\n");
    }
#endif

    return len;
}

int32_t BlueNRG_SPI_Write(SPI_HandleTypeDef *hspi, uint8_t *data1,
                          uint8_t *data2, uint8_t Nb_bytes1, uint8_t Nb_bytes2)
{
    int32_t result = 0;

    int32_t spi_fix_enabled = 0;

#ifdef ENABLE_SPI_FIX
    spi_fix_enabled = 1;
#endif // ENABLE_SPI_FIX

    unsigned char header_master[HEADER_SIZE] = {0x0a, 0x00, 0x00, 0x00, 0x00};
    unsigned char header_slave[HEADER_SIZE] = {0xaa, 0x00, 0x00, 0x00, 0x00};

    unsigned char read_char_buf[MAX_BUFFER_SIZE];

    Disable_SPI_IRQ();

    /*
    If the SPI_FIX is enabled the IRQ is set in Output mode, then it is pulled
    high and, after a delay of at least 112us, the CS line is asserted and the
    header transmit/receive operations are started.
    After these transmit/receive operations the IRQ is reset in input mode.
    */
    if (spi_fix_enabled)
    {
        set_irq_as_output();

        /* Assert CS line after at least 112us */
        us150Delay();
    }

    /* CS reset */
    HAL_GPIO_WritePin(BNRG_SPI_CS_PORT, BNRG_SPI_CS_PIN, GPIO_PIN_RESET);

    /* Exchange header */
    __disable_irq();
    HAL_SPI_TransmitReceive(hspi, header_master, header_slave, HEADER_SIZE, TIMEOUT_DURATION);
    __enable_irq();

    if (spi_fix_enabled)
    {
        set_irq_as_input();
    }

    if (header_slave[0] == 0x02)
    {
        /* SPI is ready */
        if (header_slave[1] >= (Nb_bytes1 + Nb_bytes2))
        {

            /*  Buffer is big enough */
            if (Nb_bytes1 > 0)
            {
                __disable_irq();
                HAL_SPI_TransmitReceive(hspi, data1, read_char_buf, Nb_bytes1, TIMEOUT_DURATION);
                __enable_irq();
            }
            if (Nb_bytes2 > 0)
            {
                __disable_irq();
                HAL_SPI_TransmitReceive(hspi, data2, read_char_buf, Nb_bytes2, TIMEOUT_DURATION);
                __enable_irq();
            }
        }
        else
        {
            /* Buffer is too small */
            result = -2;
        }
    }
    else
    {
        /* SPI is not ready */
        result = -1;
    }

    /* Release CS line */
    HAL_GPIO_WritePin(BNRG_SPI_CS_PORT, BNRG_SPI_CS_PIN, GPIO_PIN_SET);

    Enable_SPI_IRQ();

    return result;
}

void set_irq_as_output(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Pull IRQ high */
    GPIO_InitStructure.Pin = BNRG_SPI_IRQ_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = BNRG_SPI_IRQ_SPEED;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BNRG_SPI_IRQ_PORT, &GPIO_InitStructure);
    HAL_GPIO_WritePin(BNRG_SPI_IRQ_PORT, BNRG_SPI_IRQ_PIN, GPIO_PIN_SET);
}

void set_irq_as_input(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* IRQ input */
    GPIO_InitStructure.Pin = BNRG_SPI_IRQ_PIN;
    GPIO_InitStructure.Mode = BNRG_SPI_IRQ_MODE;
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;
    GPIO_InitStructure.Speed = BNRG_SPI_IRQ_SPEED;
    GPIO_InitStructure.Alternate = BNRG_SPI_IRQ_ALTERNATE;
    HAL_GPIO_Init(BNRG_SPI_IRQ_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pull = BNRG_SPI_IRQ_PULL;
    HAL_GPIO_Init(BNRG_SPI_IRQ_PORT, &GPIO_InitStructure);
}

static void us150Delay(void)
{
#if SYSCLK_FREQ == 4000000
    for (volatile int i = 0; i < 35; i++)
        __NOP();
#elif SYSCLK_FREQ == 32000000
    for (volatile int i = 0; i < 420; i++)
        __NOP();
#elif SYSCLK_FREQ == 80000000
    for (volatile int i = 0; i < 1072; i++)
        __NOP();
#elif SYSCLK_FREQ == 84000000
    for (volatile int i = 0; i < 1125; i++)
        __NOP();
#elif SYSCLK_FREQ == 168000000
    for (volatile int i = 0; i < 2250; i++)
        __NOP();
#else
#error Implement delay function.
#endif
}

void Enable_SPI_IRQ(void)
{
    HAL_NVIC_EnableIRQ(BNRG_SPI_EXTI_IRQn);
}

void Disable_SPI_IRQ(void)
{
    HAL_NVIC_DisableIRQ(BNRG_SPI_EXTI_IRQn);
}

void Clear_SPI_IRQ(void)
{
    HAL_NVIC_ClearPendingIRQ(BNRG_SPI_EXTI_IRQn);
}

void Clear_SPI_EXTI_Flag(void)
{
    __HAL_GPIO_EXTI_CLEAR_IT(BNRG_SPI_EXTI_PIN);
}

/******************************** End of file *********************************/
