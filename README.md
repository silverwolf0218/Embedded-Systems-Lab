# Embedded Systems Lab, Fall 2017
### For Embedded Systems Labs 2017 Fall homeworks.
## Usage
### I2C
#### RPi3與arduino連線
```
在`I2C`資料夾中

在arduino端執行i2c-Arduino.c

在RPi3端執行i2c-RPi3.c或i2c-RPi3.py
  
等待雙方連線
```
#### 讀取ADXL345數值
```
連接ADXL345

在ADXL345資料夾中

在RPi3上執行adxl345-RPi3.c或adxl345-RPi3.py

在終端機顯示讀取的三軸加速度值
```

### BLE
#### 透過藍芽傳送ADXL345數值
```
連接ADXL345

下載nodejs的bleno套件

在RPi3-BLE資料夾中

將main.js及characteristic.js複製到bleno套件底下/examples/echo資料夾，並覆蓋原本的檔案

先在一端RPi3執行main.js，另一端RPi3再開始執行RPi3-BLE-adxl345.py

在終端機顯示讀取並透過藍芽傳送的三軸加速度值
```
