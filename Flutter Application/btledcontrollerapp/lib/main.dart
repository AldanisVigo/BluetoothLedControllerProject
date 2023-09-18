import 'dart:async';
import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:flutter_blue/flutter_blue.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Bluetooth LED Controller App',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const LedControlScreen()
    );
  }
}

class LedControlScreen extends StatefulWidget {
  const LedControlScreen({super.key});
  @override
  State<StatefulWidget> createState() {
    return LedControlScreenState();
  }

}

class LedControlScreenState extends State<LedControlScreen> {
  bool connected = false;
  String deviceId = "0481F4E4-DEB4-99E6-4798-00CEBF414B59";
  String serviceId = "0000ffe0-0000-1000-8000-00805f9b34fb";
  String characteristicId = "0000ffe1-0000-1000-8000-00805f9b34fb";
  BluetoothService? uartService;
  Iterable<BluetoothCharacteristic>? uartCharacteristic;
  BluetoothDevice? ledController;
  @override
  void initState() {
    connected = false;
    
    // Scan all devices
    FlutterBlue.instance.scan().listen((ScanResult event) async { 
      if(event.device.id.id == deviceId){

        // Connect to any device whose id matches the predetermined one
        await event.device.connect(autoConnect: true);
        ledController = event.device;

        // Listen to all services within the device
        List<BluetoothService>? services = await ledController?.discoverServices();
       
        for (BluetoothService element in services ?? []) { 
          
          uartCharacteristic = element.characteristics.where((charac)=>charac.uuid.toString() == characteristicId);
          if(uartCharacteristic != null){
            uartService = element;
            // await uartCharacteristic?.first.write(utf8.encode("LED0\n"));
            // Future.delayed(const Duration(seconds: 5), () async => await uartCharacteristic?.first.write(utf8.encode("LED0\n"), withoutResponse: true)); 
            print("UART CHARACTERISTIC UUID: ${uartCharacteristic?.first.uuid.toString()}");
          }
        }
      }
    });
    super.initState();
  }

  @override
  void dispose() {
    super.dispose();
  }

  bool ledRedOn = false;
  bool ledGreenOn = false;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Bluetooth LED Controller")
      ),
      body: SingleChildScrollView(
        child: Column(
          children: [
            TextButton(
              child: Center(child: ledGreenOn ? Image.asset("assets/images/led_green_on.png") : Image.asset("assets/images/led_green_off.png")),
              onPressed: () async {
                await uartCharacteristic?.first.write(utf8.encode("LED0\n"), withoutResponse: true);
                await uartCharacteristic?.first.read();
                setState(() {
                  ledGreenOn = !ledGreenOn;
                });
              },
            ),
            TextButton(
              child: Center(child: ledRedOn ? Image.asset("assets/images/led_red_on.png") : Image.asset("assets/images/led_red_off.png")),
              onPressed: () async {
                await uartCharacteristic?.first.write(utf8.encode("LED1\n"), withoutResponse: true);
                await uartCharacteristic?.first.read();
                setState(() {
                  ledRedOn = !ledRedOn;
                });
              },
            )
          ],
        ),
      )
    );
  }
}