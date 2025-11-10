# DJI Ronin S Remote Control con ESP32

Controlla un **Gimbal DJI Ronin S** tramite un controller Bluetooth usando un **ESP32 ⚡**. La comunicazione con il gimbal avviene tramite il protocollo **S.BUS**, gestito dalla libreria custom `Ronin_SBUS.h`.

---

## ✨ Funzionalità principali
- 🕹️ Controllo **Pan** e **Tilt** del gimbal tramite joystick del controller.
- 🎮 Supporto a **Switch Pro Controller** e altri controller compatibili con [Bluepad32](https://github.com/ricardoquesada/bluepad32).
- ⚡ Modalità di velocità normale o ridotta, attivabile con il tasto `B`.
- 📡 Invio dei dati S.BUS tramite la libreria custom `Ronin_SBUS.h`.
- 🛠️ Compatibile con il microcontrollore **ESP32**

## 🚀 Come usare
1. Caricare lo sketch su ESP32/Arduino.
2. Accendere il controller Bluetooth e impostarlo in modalità di associazione.
3. Muovere il joystick per controllare Pan e Tilt.
4. Premere il tasto `B` per passare alla modalità velocità ridotta.

## 🔧 Requisiti hardware e software
- ESP32 o Arduino compatibile.
- Libreria **Bluepad32** installata.
- Libreria custom `Ronin_SBUS.h`.
- Gimbal DJI Ronin S con input S.BUS.

## 🔌 Schema di collegamento

| DJI Ronin S | ESP32 |
|-------------|-------|
| 5V          | VIN   |
| GND         | GND   |
| S.BUS Data  | D17   |

💡 **Note:**
- Assicurati che l’ESP32 sia alimentato correttamente tramite VIN a 5V.
- Il pin D17 è usato come TX per inviare dati S.BUS al gimbal.
- Non invertire i collegamenti GND/5V per evitare danni all’hardware.

## 💻 Software Setup

1. **Installare le librerie Arduino necessarie:**
   - [Bluepad32](https://github.com/ricardoquesada/bluepad32)  
     ```text
     Arduino Library Manager → Cerca "Bluepad32" → Installa
     ```
   - `Ronin_SBUS`  
     Copia la cartella della libreria presente nella cartella **Codice** di questo repository nella tua cartella **libraries** di Arduino.

2. **Caricare il codice su ESP32:**  
   - Collegare l’ESP32 al computer tramite USB.  
   - Aprire lo sketch `.ino` nel software Arduino IDE.  
   - Selezionare la scheda ESP32 corretta e la porta COM appropriata.  
   - Cliccare su **Upload**.

💡 **Suggerimenti:**  
- Assicurati che tutte le librerie siano aggiornate.  
- Controlla che l’ESP32 sia correttamente alimentato e connesso al gimbal prima di testare il controllo.  

## 🙏 Ringraziamenti

Un grazie speciale a tutti coloro che hanno reso possibile questo progetto:

- Lo sviluppatore originale della libreria **[BMC_SBUS]**(https://github.com/boldstelvis/BMC_SBUS), da cui è nata la libreria `Ronin_SBUS` utilizzata in questo progetto.
- Tutti i contributori della libreria **[Bluepad32]**(https://github.com/ricardoquesada/bluepad32), indispensabile per il supporto ai controller Bluetooth.
