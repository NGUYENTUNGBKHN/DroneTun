/**
 * @file       app_main.c
 * @brief      
 * @date       2026/05/24
 * @author     [Gentantun] (nguyenthanhtung8196@gmail.com)
 * @details    
 * @ref        
 * @copyright  Copyright (c) 2026 RoboTun
*/

/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "app_main.h"
#include "SPBTLE_RF.h"
#include "bluenrg_gatt_server.h"
#include "bluenrg_utils.h"
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/


/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/
extern uint8_t set_connectable;

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
volatile uint32_t HCI_ProcessEvent=0;
// SPI_HandleTypeDef hspi1;
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
int32_t BytesToWrite;
uint8_t BufferToWrite[256];
uint8_t bdaddr[6];
DrvStatusTypeDef testStatus = COMPONENT_OK;
uint16_t service_handle, dev_name_char_handle, appearance_char_handle;
uint32_t ConnectionBleStatus=0;
uint8_t joydata[8] = {0,0,0,0,0,0,0,0};
/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
static void Init_BlueNRG_Custom_Services(void)
{
    int ret;

    ret = Add_HWServW2ST_Service();
    if (ret == BLE_STATUS_SUCCESS)
    {
        PRINTF("HW      Service W2ST added successfully\r\n");
    }
    else
    {
        PRINTF("\r\nError while adding HW Service W2ST\r\n");
    }

    ret = Add_ConsoleW2ST_Service();
    if (ret == BLE_STATUS_SUCCESS)
    {
        PRINTF("Console Service W2ST added successfully\r\n");
    }
    else
    {
        PRINTF("\r\nError while adding Console Service W2ST\r\n");
    }

    ret = Add_ConfigW2ST_Service();
    if (ret == BLE_STATUS_SUCCESS)
    {
        PRINTF("Config  Service W2ST added successfully\r\n");
    }
    else
    {
        PRINTF("\r\nError while adding Config Service W2ST\r\n");
    }
}

void BlueNRG_Init(void)
{

    int ret = 1;
    uint8_t hwVersion = 0;
    uint16_t fwVersion = 0;

    PRINTF("****** START BLE TESTS ******\r\n");
    BNRG_SPI_Init();

    /* Commented on Jan 15, 2020 */
    // uint8_t tmp_bdaddr[6]= {MAC_BLUEMS};
    // int32_t i;
    /* Commented on Jan 15, 2020 */
    // for(i=0;i<6;i++)
    //   bdaddr[i] = tmp_bdaddr[i];
    HAL_Delay(10);

    /* Added on Jan 15, 2020 */
    bdaddr[0] = (STM32_UUID[1] >> 24) & 0xFF;
    bdaddr[1] = (STM32_UUID[0]) & 0xFF;
    bdaddr[2] = (STM32_UUID[2] >> 8) & 0xFF;
    bdaddr[3] = (STM32_UUID[0] >> 16) & 0xFF;
    bdaddr[4] = (hwVersion > 0x30) ? ((((0x34 - 48) * 10) + (0x30 - 48) + 100) & 0xFF) : ((((0x34 - 48) * 10) + (0x30 - 48)) & 0xFF);
    bdaddr[5] = 0xC0; /* for a Legal BLE Random MAC */

    /* Initialize the BlueNRG HCI */
    HCI_Init();

    /* Reset BlueNRG hardware */
    BlueNRG_RST();

    /* get the BlueNRG HW and FW versions */
    PRINTF("\r\nReading BlueNRG version ...\r\n");
    if (getBlueNRGVersion(&hwVersion, &fwVersion) == BLE_STATUS_SUCCESS)
    {

        /*
         * Reset BlueNRG again otherwise it will fail.
         */
        BlueNRG_RST();

        // PRINTF("Setting Pubblic Address...\r\n");
        /* Commented on Jan 15, 2020 */
        // ret = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET,
        //                                 CONFIG_DATA_PUBADDR_LEN,
        //                                 bdaddr);
        // if(ret){
        //   testStatus = COMPONENT_ERROR;
        //   PRINTF("\r\nSetting Pubblic BD_ADDR failed *****\r\n");
        //   goto fail;
        // }

        PRINTF("GATT Initializzation...\r\n");
        ret = aci_gatt_init();
        if (ret)
        {
            testStatus = COMPONENT_ERROR;
            PRINTF("\r\nGATT_Init failed ****\r\n");
            goto fail;
        }

        //    ret = aci_gatt_update_char_value(service_handle, dev_name_char_handle, 0,
        //                                     7/*strlen(BoardName)*/, (uint8_t *)BoardName);
        //
        //    if(ret){
        //       PRINTF("\r\naci_gatt_update_char_value failed\r\n");
        //      while(1);
        //    }

        /* Set the GAP INIT like X-NUCLEO-IDB05A1 eval board  since using same SPBTLE_RF module*/
        ret = aci_gap_init_IDB05A1(GAP_PERIPHERAL_ROLE_IDB05A1, 0, 0x07, &service_handle, &dev_name_char_handle, &appearance_char_handle);

        if (ret != BLE_STATUS_SUCCESS)
        {
            PRINTF("\r\nGAP_Init failed\r\n");
            goto fail;
        }

        // Added Jan 10th
        ret = hci_le_set_random_address(bdaddr);
        // Added Jan 10th
        const char BoardName[7] = {NAME_BLUEMS};
        // Added Jan 10th
        ret = aci_gatt_update_char_value(service_handle, dev_name_char_handle, 0,
                                         7 /*strlen(BoardName)*/, (uint8_t *)BoardName);

        PRINTF("GAP setting Authentication ....\r\n");
        ret = aci_gap_set_auth_requirement(MITM_PROTECTION_REQUIRED,
                                           OOB_AUTH_DATA_ABSENT,
                                           NULL, 7, 16,
                                           USE_FIXED_PIN_FOR_PAIRING, 123456,
                                           BONDING);
        if (ret != BLE_STATUS_SUCCESS)
        {
            testStatus = COMPONENT_ERROR;
            PRINTF("\r\nGAP setting Authentication failed ******\r\n");
            goto fail;
        }

        PRINTF("SERVER: BLE Stack Initialized \r\n"
               "Board HWver=%d, FWver=%d.%d.%c\r\n"
               "BoardMAC = %x:%x:%x:%x:%x:%x\r\n",
               hwVersion,
               fwVersion >> 8,
               (fwVersion >> 4) & 0xF,
               (hwVersion > 0x30) ? ('a' + (fwVersion & 0xF) - 1) : 'a',
               bdaddr[5], bdaddr[4], bdaddr[3], bdaddr[2], bdaddr[1], bdaddr[0]);

        /* Set output power level */
        aci_hal_set_tx_power_level(1, 4); /* -2.1dBm */

        PRINTF("\r\nAll test passed!\r\n");
    }
    else
    {
        testStatus = COMPONENT_ERROR;
        PRINTF("\r\nError in BlueNRG tests. ******\r\n");
    }
    PRINTF("****** END BLE TESTS ******\r\n");
    return;

fail:
    testStatus = COMPONENT_ERROR;
    return;
}

/**
 * @brief  Initializes the SPI MSP (low-level hardware)
 * @note   This function configures GPIO pins and enables the SPI clock
 * @param  hspi: pointer to a SPI_HandleTypeDef structure
 * @retval None
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (hspi->Instance == SPI1)
    {
        /* Enable SPI1 clock */
        BNRG_SPI_CLK_ENABLE();

        /* Enable GPIO clocks */
        BNRG_SPI_SCLK_CLK_ENABLE();
        BNRG_SPI_MISO_CLK_ENABLE();
        BNRG_SPI_MOSI_CLK_ENABLE();
        BNRG_SPI_CS_CLK_ENABLE();
        BNRG_SPI_RESET_CLK_ENABLE();
        BNRG_SPI_IRQ_CLK_ENABLE();

        /* Configure SCLK (PA.5) */
        GPIO_InitStruct.Pin = BNRG_SPI_SCLK_PIN;
        GPIO_InitStruct.Mode = BNRG_SPI_SCLK_MODE;
        GPIO_InitStruct.Pull = BNRG_SPI_SCLK_PULL;
        GPIO_InitStruct.Speed = BNRG_SPI_SCLK_SPEED;
        GPIO_InitStruct.Alternate = BNRG_SPI_SCLK_ALTERNATE;
        HAL_GPIO_Init(BNRG_SPI_SCLK_PORT, &GPIO_InitStruct);

        /* Configure MISO (PA.6) */
        GPIO_InitStruct.Pin = BNRG_SPI_MISO_PIN;
        GPIO_InitStruct.Mode = BNRG_SPI_MISO_MODE;
        GPIO_InitStruct.Pull = BNRG_SPI_MISO_PULL;
        GPIO_InitStruct.Speed = BNRG_SPI_MISO_SPEED;
        GPIO_InitStruct.Alternate = BNRG_SPI_MISO_ALTERNATE;
        HAL_GPIO_Init(BNRG_SPI_MISO_PORT, &GPIO_InitStruct);

        /* Configure MOSI (PA.7) */
        GPIO_InitStruct.Pin = BNRG_SPI_MOSI_PIN;
        GPIO_InitStruct.Mode = BNRG_SPI_MOSI_MODE;
        GPIO_InitStruct.Pull = BNRG_SPI_MOSI_PULL;
        GPIO_InitStruct.Speed = BNRG_SPI_MOSI_SPEED;
        GPIO_InitStruct.Alternate = BNRG_SPI_MOSI_ALTERNATE;
        HAL_GPIO_Init(BNRG_SPI_MOSI_PORT, &GPIO_InitStruct);

        /* Configure CS/NSS (PB.0) */
        GPIO_InitStruct.Pin = BNRG_SPI_CS_PIN;
        GPIO_InitStruct.Mode = BNRG_SPI_CS_MODE;
        GPIO_InitStruct.Pull = BNRG_SPI_CS_PULL;
        GPIO_InitStruct.Speed = BNRG_SPI_CS_SPEED;
        HAL_GPIO_Init(BNRG_SPI_CS_PORT, &GPIO_InitStruct);
        HAL_GPIO_WritePin(BNRG_SPI_CS_PORT, BNRG_SPI_CS_PIN, GPIO_PIN_SET);

        /* Configure Reset pin (PB.2) */
        GPIO_InitStruct.Pin = BNRG_SPI_RESET_PIN;
        GPIO_InitStruct.Mode = BNRG_SPI_RESET_MODE;
        GPIO_InitStruct.Pull = BNRG_SPI_RESET_PULL;
        GPIO_InitStruct.Speed = BNRG_SPI_RESET_SPEED;
        HAL_GPIO_Init(BNRG_SPI_RESET_PORT, &GPIO_InitStruct);
        HAL_GPIO_WritePin(BNRG_SPI_RESET_PORT, BNRG_SPI_RESET_PIN, GPIO_PIN_RESET);

        /* Configure IRQ pin (PA.4) - with external interrupt */
        GPIO_InitStruct.Pin = BNRG_SPI_IRQ_PIN;
        GPIO_InitStruct.Mode = BNRG_SPI_IRQ_MODE;
        GPIO_InitStruct.Pull = BNRG_SPI_IRQ_PULL;
        GPIO_InitStruct.Speed = BNRG_SPI_IRQ_SPEED;
        HAL_GPIO_Init(BNRG_SPI_IRQ_PORT, &GPIO_InitStruct);

        /* Enable EXTI interrupt for SPI IRQ */
        HAL_NVIC_SetPriority(BNRG_SPI_EXTI_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(BNRG_SPI_EXTI_IRQn);

        /* Enable SPI1 interrupt */
        HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(SPI1_IRQn);
    }
}

int app_main()
{
    /* Essential function initialize */
    mcu_init();

    TRACE_INFO("BLE communication initialization...\n\n");

    BlueNRG_Init();
    /* Initialize the BlueNRG Custom services */
    Init_BlueNRG_Custom_Services();

    TRACE_INFO("Application --> Start 2\n");
    while (1)
    {
        /* code */
        if (HCI_ProcessEvent)
        {
            HCI_ProcessEvent = 0;
            HCI_Process();
        }

        if (set_connectable)
        {
            /* Now update the BLE advertize data and make the Board connectable */
            if (setConnectable() == BLE_STATUS_SUCCESS)
            {
                set_connectable = FALSE;
            }
        }
    }
}

/******************************** End of file *********************************/
