#include "mcu/mcu.h"
#include "main.h"
#include "board/buttoncontroller.h"
#include "platform/f7-disco-gcc/board/ButtonController.h"

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin)
    {
    case BUTTON0_Pin:
    case BUTTON1_Pin:
    case BUTTON2_Pin:
    case BUTTON3_Pin:
        ButtonController::getInstance().onIrq();
        break;
    default:
        break;
    }
}
