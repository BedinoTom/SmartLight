import machine
import sensor,image,lcd,time
from board import board_info
import KPU as kpu

board_info.load({
    'PIN_8': 14,
    'PIN_9': 13,
    'BOOT_KEY': 16,
})

from fpioa_manager import fm
fm.register(board_info.PIN_8, fm.fpioa.GPIOHS0, force=True)
fm.register(board_info.PIN_9, fm.fpioa.GPIOHS1, force=True)

from Maix import GPIO

def test_irq(pin_num):
    print("key", pin_num)

key=GPIO(GPIO.GPIOHS0, GPIO.IN, GPIO.PULL_UP)
key2=GPIO(GPIO.GPIOHS1, GPIO.OUT)
key.irq(test_irq, GPIO.IRQ_BOTH, GPIO.WAKEUP_NOT_SUPPORT, 7)

lcd.init(freq=15000000)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_vflip(1)
sensor.run(1)
clock = time.clock()
classes = ['aeroplane', 'bicycle', 'bird', 'boat', 'bottle', 'bus', 'car', 'cat', 'chair', 'cow', 'diningtable', 'dog', 'horse', 'motorbike', 'person', 'pottedplant', 'sheep', 'sofa', 'train', 'tvmonitor']
task = kpu.load(0x500000)
anchor = (1.08, 1.19, 3.42, 4.41, 6.63, 11.38, 9.42, 5.11, 16.62, 10.52)
a = kpu.init_yolo2(task, 0.5, 0.3, 5, anchor)
while(True):
    clock.tick()
    img = sensor.snapshot()
    code = kpu.run_yolo2(task, img)
    print(clock.fps())
    if code:
        for i in code:
            a=img.draw_rectangle(i.rect())
            img.draw_string(i.x(), i.y(), classes[i.classid()], color=(255, 0, 0), scale=2)
            img.draw_string(i.x(), i.y()+24, '%.3f'%i.value(), color=(255, 0, 0), scale=2)
            a = lcd.display(img)
            if classes[i.classid()] == "person":
                key2.value(1)
    else:
        key2.value(0)
        a = lcd.display(img)
a = kpu.deinit(task)
