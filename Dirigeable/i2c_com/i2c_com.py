# Untitled - By: tombe - lun. févr. 7 2022

import machine
import sensor,image,lcd,time
from board import board_info

board_info.load({
    'PIN_8': 14,
    'BOOT_KEY': 16,
})

from fpioa_manager import fm
fm.register(board_info.PIN_8, fm.fpioa.GPIOHS0, force=True)

from Maix import GPIO

def test_irq(pin_num):
    print("key", pin_num)

key=GPIO(GPIO.GPIOHS0, GPIO.IN, GPIO.PULL_UP)
key.irq(test_irq, GPIO.IRQ_BOTH, GPIO.WAKEUP_NOT_SUPPORT, 7)

lcd.init(freq=15000000)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_vflip(1)
sensor.run(1)
clock = time.clock()
while(True):
    clock.tick()
    img = sensor.snapshot()
    img.draw_string(10, 24, str(key.value()), color=(255, 0, 0), scale=2)
    a = lcd.display(img)



