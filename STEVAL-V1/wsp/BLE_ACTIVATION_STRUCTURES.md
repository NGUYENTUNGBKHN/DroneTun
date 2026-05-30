# Tom tat cau truc kich hoat Bluetooth BlueNRG

File nay gom cac cau truc, bien va handle quan trong de Bluetooth BlueNRG hoat dong trong project.

## 1. Tang phan cung SPI/GPIO

- `SPI_HandleTypeDef SpiHandle`
  - Khai bao tai `Middleware/BSP/Components/spbtle_rf/SPBTLE_RF.c`
  - Day la SPI handle thuc su duoc BlueNRG middleware su dung.

- `GPIO_InitTypeDef GPIO_InitStruct`
  - Dung trong `Application/app_main.c`, ham `HAL_SPI_MspInit()`
  - Cau hinh cac chan SCLK, MISO, MOSI, CS, RESET va IRQ.

- Cac macro cau hinh BlueNRG SPI/GPIO
  - Nam trong `Middleware/BSP/Components/spbtle_rf/SPBTLE_RF.h`
  - Quan trong gom:
    - `BNRG_SPI_INSTANCE`
    - `BNRG_SPI_RESET_PIN`
    - `BNRG_SPI_CS_PIN`
    - `BNRG_SPI_IRQ_PIN`
    - `BNRG_SPI_EXTI_IRQn`

Luu y: `Application/app_main.c` co bien `SPI_HandleTypeDef hspi1`, nhung BlueNRG dang dung `SpiHandle` trong `SPBTLE_RF.c`.

## 2. Tang HCI

- `volatile uint32_t HCI_ProcessEvent`
  - Khai bao tai `Application/app_main.c`
  - Co bao co su kien HCI tu BlueNRG.

- `tHciDataPacket`
  - Khai bao trong `Middleware/STM32_BlueNRG/SimpleBlueNRG_HCI/includes/hci.h`
  - Dung lam buffer nhan goi HCI.

- `hciReadPktPool`, `hciReadPktRxQueue`
  - Khai bao trong `hci.h`
  - Queue chua cac goi HCI da nhan.

Luong xu ly su kien:

```text
EXTI4_IRQHandler()
  -> HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4)
  -> HAL_GPIO_EXTI_Callback()
  -> HCI_Isr()
  -> HCI_ProcessEvent = 1
  -> vong while trong app_main() goi HCI_Process()
```

## 3. GAP/GATT co ban

- `uint8_t bdaddr[6]`
  - Khai bao tai `Application/app_main.c`
  - Dia chi BLE random/static random.

- `uint16_t service_handle`
  - GAP service handle.

- `uint16_t dev_name_char_handle`
  - Device Name characteristic handle.

- `uint16_t appearance_char_handle`
  - Appearance characteristic handle.

Trinh tu khoi tao chinh trong `BlueNRG_Init()`:

```c
BNRG_SPI_Init();
HCI_Init();
BlueNRG_RST();
getBlueNRGVersion(&hwVersion, &fwVersion);
BlueNRG_RST();
aci_gatt_init();
aci_gap_init_IDB05A1(...);
hci_le_set_random_address(bdaddr);
aci_gatt_update_char_value(...);   // cap nhat ten thiet bi
aci_gap_set_auth_requirement(...);
aci_hal_set_tx_power_level(...);
```

## 4. Custom BLE services va characteristics

Nam trong `Application/User/bluetooth/ble.c`.

### Hardware service

- `HWServW2STHandle`
- `EnvironmentalCharHandle`
- `AccGyroMagCharHandle`
- `AccEventCharHandle`
- `ArmingCharHandle`
- `MaxCharHandle`

Ham tao service:

```c
Add_HWServW2ST_Service();
```

### Console service

- `ConsoleW2STHandle`
- `TermCharHandle`
- `StdErrCharHandle`

Ham tao service:

```c
Add_ConsoleW2ST_Service();
```

### Config service

- `ConfigServW2STHandle`
- `ConfigCharHandle`

Ham tao service:

```c
Add_ConfigW2ST_Service();
```

UUID cua cac service/characteristic nam trong:

```text
Application/User/bluetooth/uuid_ble_service.h
```

## 5. Trang thai ket noi va advertise

- `uint8_t set_connectable`
  - Nam trong `Application/User/bluetooth/ble.c`
  - Neu bang `TRUE`, vong while trong `app_main()` se goi `setConnectable()`.

- `uint32_t ConnectionBleStatus`
  - Nam trong `Application/app_main.c`
  - Bitmask trang thai client da subscribe characteristic nao.

- `static uint16_t connection_handle`
  - Nam trong `Application/User/bluetooth/ble.c`
  - Handle cua ket noi BLE hien tai.

Ham advertise:

```c
setConnectable();
```

Ham nay goi:

```c
hci_le_set_scan_resp_data(0, NULL);
aci_gap_set_discoverable(...);
aci_gap_update_adv_data(...);
```

## 6. Cac callback quan trong

- `GAP_ConnectionComplete_CB()`
  - Dat `connected = TRUE`
  - Luu `connection_handle`
  - Reset `ConnectionBleStatus`

- `GAP_DisconnectionComplete_CB()`
  - Dat `connected = FALSE`
  - Dat `set_connectable = TRUE` de advertise lai
  - Reset `ConnectionBleStatus`

- `Attribute_Modified_CB()`
  - Xu ly subscribe/unsubscribe notification
  - Xu ly data client ghi vao characteristic
  - Nhan du lieu joystick qua `MaxCharHandle + 1` va ghi vao `joydata[]`

- `Read_Request_CB()`
  - Xu ly yeu cau read characteristic tu client.

## 7. Diem can kiem tra

Trong `BlueNRG_Init()` hien dang add:

```c
Add_ConsoleW2ST_Service();
Add_ConfigW2ST_Service();
```

Sau do `app_main()` lai goi:

```c
Init_BlueNRG_Custom_Services();
```

Ham nay add lai:

```c
Add_HWServW2ST_Service();
Add_ConsoleW2ST_Service();
Add_ConfigW2ST_Service();
```

Neu BLE khong advertise, khong connect duoc, hoac add service bi loi, can kiem tra viec add `Console` va `Config` bi lap hai lan.

