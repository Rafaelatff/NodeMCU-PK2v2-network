# NodeMCU-PK2v2-network
Network configuration of a NodeMCU using a PK2v2 from WissTek lab.

## Wireless configuration

We will keep part of the code that we had been use during the "things" and serial monitor configuration for the PK2v2 board. It is possible to consult it here: [NodeMCU-PK2v2-things](https://github.com/Rafaelatff/NodeMCU-PKv2-things).

Let's focus on the network configuration. We will be using a known network for that. Let's start by adding the libary *<ESP8266WiFi.h>* and creating two variables with type *const char* to hold our ssid and password.

![image](https://user-images.githubusercontent.com/58916022/220408137-9891aa92-65ae-4066-8413-9f2680c63373.png)

Then, inside the 'void setup()', we will add code to configure both serial monitor and Wifi.

We will start by calling the WiFi.begin class function.

![image](https://user-images.githubusercontent.com/58916022/220412070-a9dec70d-e0c7-4648-8eb8-fc8b328f8471.png)

And then we wait inside a while loop until 'WiFi.status()' return a value different than *WL_CONNECTED*.

```c
void setup() {
  // put your setup code here, to run once:

  // Configure seria monitor
  Serial.begin(115200);
  delay(1000);

  Serial.print("\r\n"); // new line and carriage return
  Serial.print("Conectando a rede ");
  Serial.println(ssid);

  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}
```

Then, when 'WiFi.status()' return the value *WL_CONNECTED*, we will print that the wifi network is connected and its IP addres, by using the WiFi.localIP() class fucntion.

```c
  Serial.println(" ");
  Serial.println("WiFi Conectado");
  Serial.println("Endereço de IP:");
  Serial.println(WiFi.localIP());
```

Results:

As it is possible to see below, the Serial Monitor shows a lot of "trash" before starting to send the information that we coded to show.

![trash-serial-monitor](https://user-images.githubusercontent.com/58916022/220403822-c7b4ede3-523b-4437-85a3-e9f214245930.PNG)

The explanation is because when we reset the NodeMCU, the board send some information in a different baud rate. If we change the baud rate of the terminal we will be able to read the data printed on the Serial Monitor. But then, our data will start to look like trash. We can just ignore that, clean the Serial Monitor our start to send our information at same baud rate (74880).

![image](https://user-images.githubusercontent.com/58916022/220406391-227582c6-faee-47ad-901e-3e9e1b860f64.png)

After adjusting the code:

![image](https://user-images.githubusercontent.com/58916022/220420464-45d802d2-2bca-40ce-9ec8-a791873f1844.png)

## WiFi Scan

Let's test a different code, that searchs for the nearby networks. In resume, we keep using the library "ESP8266WiFi.h".

![image](https://user-images.githubusercontent.com/58916022/220433634-636df9e8-62c7-4e62-8ca5-fd520e25ec6f.png)

The 'void setup()' only receives the commands to change the *WiFi.mode* to *WIFI_STA* (wifi station). Also, the code makes sure that the access point (AP) isn't connected to a network

```c
  // Coloca no modo WiFi Station (WiFi_STA)
  WiFi.mode(WIFI_STA);
  // Desconecta de um AP que estava previamente conectado para poder fazer o WiFi Scan
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
```

Then, in 'void Loop()', using the *WiFi.scanNetworks* class function, we will attribute to the variable 'n' the number of network found.

```c
 // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
```

Then we will check if this value is equal to 0 (not a single network found).

```c
  if (n == 0) {
    Serial.println(" Não foi encontrada nenhuma rede");
  }
``` 

And in case of network found, it will print the number of networks.

```c
 else {
  Serial.print("Redes WiFi encontradas = ");
  Serial.println(n);
 ```
 
 Then we will print on Serial Monitor all network found (its SSID - Service Set Identifier).
 
 ```c
  for (int i = 0; i < n; ++i) {
  // Apresenta no serial monitor o SSID e a RSSI de cada rede encontrada
  Serial.print(i + 1);
  Serial.print(" - SSID: ");
  Serial.print(WiFi.SSID(i));
```

Then we will print, at the same line, the received RSSI - Received Signal Strength Indicator of the network.

```c  
  Serial.print("  -  RSSI = ");
  Serial.print(WiFi.RSSI(i));
  Serial.println("");
  delay(10);
 }
 ```
 
For more info, the libs can be consulted.

![image](https://user-images.githubusercontent.com/58916022/220495505-12a19dd0-d96d-45a4-8e75-0996d1e4b722.png)
 
Then it will be in loop of a few seconds.

Results:

![image](https://user-images.githubusercontent.com/58916022/220433410-c7995c3b-5a3c-4a72-a975-2960c06d9f30.png)


