# Device driver

To compile this driver:
```
sudo apt install raspberrypi-kernel-headers
cmake .

make driver
make load
```

To test if the driver is working:
```
root@pi:/home/vault/device-driver# cat /proc/devices | grep Laar-Verdult
509 Laar-Verdult-driver
root@pi:/home/vault/device-driver# mknod /dev/Laar-Verdult-driver c 509 0 
root@pi:/home/vault/device-driver# cat /dev/Laar-Verdult-driver 
Hello world from kernel mode!
```