import serial

# 設定串口參數，通常Arduino使用9600波特率
ser = serial.Serial('COM3', 9600, timeout=1)

try:
    while True:
        # 讓使用者輸入0或1
        user_input = input("請輸入0或1：")

        # 檢查輸入是否合法
        if user_input in ['0', '1']:
            # 將使用者輸入的值傳送給Arduino
            ser.write(user_input.encode())
            print(f"已傳送 {user_input} 到 Arduino")
        else:
            print("請輸入有效的值 (0 或 1)")

except KeyboardInterrupt:
    # 當使用者按下Ctrl+C停止程式時，關閉串口
    ser.close()
    print("程式結束")
