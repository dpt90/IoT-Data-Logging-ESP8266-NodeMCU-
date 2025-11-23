# IoT-Data-Logging-ESP8266-NodeMCU-

---

# **IoT Temperature Monitoring System Using ESP8266 and TMP36**

## **Abstract**

This project presents the design and implementation of a low-cost IoT-based temperature monitoring system using the ESP8266 (NodeMCU) microcontroller and the TMP36 analog temperature sensor. The system measures ambient temperature and hosts a local web server that visualizes real-time data using HTML, CSS, and Chart.js. The developed solution enables sensor data monitoring without dependency on cloud platforms, making it suitable for laboratory use, controlled environments, offline IoT systems, and edge computing applications.

---

## **System Overview**

The system continuously measures temperature using the TMP36 sensor and transmits the data to a web interface hosted locally by the ESP8266. The web dashboard includes:

* Real-time sensor readings (°C)
* Auto-refreshed line graph
* 5-second interval data logging
* Local access through Wi-Fi (no internet required)

---

## **Hardware Components**

| Component                | Quantity |
| ------------------------ | -------- |
| ESP8266 NodeMCU          | 1        |
| TMP36 Temperature Sensor | 1        |
| Male-Female Jumper Wires | 3        |
| Breadboard (Optional)    | 1        |

---

## **Circuit Connections**

| TMP36 Pin     | ESP8266 Pin |
| ------------- | ----------- |
| VOUT          | A0          |
| VCC (5V/3.3V) | 3.3V        |
| GND           | GND         |

> ⚠️ The TMP36 **operates safely on 3.3V**, which is compatible with ESP8266.
> Ensure that **no 5V signal** is connected to the A0 pin.

---

## **Software & Libraries**

No external Arduino libraries are required.
The dashboard uses Chart.js via CDN (loaded in browser).

**Required tools:**

* Arduino IDE
* ESP8266 Board Manager Installed
* USB Data Cable

---

## **Code Functionality**

* Reads analog voltage from TMP36 through `A0`.
* Converts voltage to temperature using the formula:
  [
  T(°C) = (V_{out} - 0.5) \times 100
  ]
* Creates a web server on port 80.
* Exposes two routes:

  * `/` → HTML dashboard interface
  * `/temp` → API returning the current sensor temperature
* JavaScript fetches data every 5 seconds and updates a line chart.

---

## **How to Run**

1. Install ESP8266 board in Arduino IDE.
2. Replace Wi-Fi credentials in code:

   ```cpp
   const char* ssid = "YOUR_WIFI_NAME";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```
3. Upload the code to NodeMCU.
4. Open Serial Monitor to obtain the IP address.
5. Enter the IP into a browser (e.g., `http://192.168.x.x/`).

---

## **Applications**

* Laboratory temperature measurement
* Indoor environmental monitoring
* IoT-based smart home controls
* Edge computing without cloud dependency
* Remote monitoring in restricted network areas

---


## **Conclusion**

The proposed system demonstrates a cost-effective IoT solution for continuous temperature monitoring using a microcontroller-based embedded system. By implementing a local data visualization mechanism, it eliminates dependence on cloud services, making it suitable for offline environments, research labs, and educational demonstrations.

---

