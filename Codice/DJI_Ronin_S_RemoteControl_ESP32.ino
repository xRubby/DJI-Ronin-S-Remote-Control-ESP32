#include <Ronin_SBUS.h>
#include <Bluepad32.h>

// --- Controller ---
ControllerPtr myController = nullptr;

// --- Interfaccia S.BUS per Ronin ---
Ronin_SBUS ronin;
#define SBUS_PIN 14         // PIN ESP32

// --- Costanti S.BUS ---
const int sbusMID = 1024;   // Neutral val
const int sbusMIN = 352;    // Min usable for analog val and switch val
const int sbusMAX = 1696;   // Max usable for analog val and switch val
const int sbusWAIT = 10;    // Frame timing delay in msecs

// --- Variabili per la gestione della modalità di movimento (veloce o lenta) ---
bool lowspeed=false;
bool prevBState = false;

// --- Callback quando un controller si connette ---
void onConnectedController(ControllerPtr ctl) {
  if (myController == nullptr) {
    Serial.println("CALLBACK: Controller is connected");
    myController = ctl;
  }
}

// --- Callback quando un controller si disconnette ---
void onDisconnectedController(ControllerPtr ctl) {
  if (myController == ctl) {
    Serial.println("CALLBACK: Controller disconnected");
    myController = nullptr;
  }
}

// --- Funzione di mapping da joystick (-500..500) a valori S.BUS ---
int16_t mapToSbus(int16_t value) {
  // map da -500/500 → sbMIN/sbMAX
  const int deadzone = 50;  // intervallo attorno allo zero considerato neutro

  // Se siamo nella zona morta, restituisci valore neutro
  if(abs(value) < deadzone) {
    return sbusMID;
  }

  // Mappatura lineare da -500..500 a sbusMIN..sbusMAX
  int16_t mapped;

  // Se è attiva la modalità lenta, i movimenti verranno eseguiti a velocità ridotta;
  // altrimenti verranno eseguiti a velocità normale.
  if(lowspeed){
    mapped = map(value/2, -500, 500, sbusMIN, sbusMAX);
  }else{
    mapped = map(value, -500, 500, sbusMIN, sbusMAX);
  }

  // Assicura che il valore non superi i limiti S.Bus
  if(mapped < sbusMIN) return sbusMIN;
  if(mapped > sbusMAX) return sbusMAX;

  return mapped;
}

void changeSpeed(){
  lowspeed = !lowspeed;

  Serial.println("Velocità impostata su " + String(lowspeed));
}

void setup() {
  Serial.begin(115200);
  
  // Inizializza Ronin S.Bus
  ronin.begin(SBUS_PIN);

  // Inizializza Bluepad32 con callback di connessione e disconnessione
  BP32.setup(&onConnectedController, &onDisconnectedController);

  // Resetta le chiavi Bluetooth precedentemente salvate
  // Utile se ci sono problemi di riconnessione
  BP32.forgetBluetoothKeys();
}

void loop() {

  // Aggiorna lo stato dei controller
  bool dataUpdated = BP32.update();

  // Se ci sono dati nuovi e il controller è connesso
  if(dataUpdated && myController != nullptr) {
    
    //Se viene premuto il tasto B (A per Switch Pro Controller) la velocità viene dimezzata
    bool currentBState = myController->b();

    if (currentBState && !prevBState) {
      changeSpeed();
    }

    // Aggiorna lo stato precedente del tasto
    prevBState = currentBState;

    // Leggi gli assi del controller e mappa su valori S.Bus
    int16_t pan  = mapToSbus(myController->axisX());
    int16_t tilt = mapToSbus(myController->axisY());

    // Aggiorna i canali Ronin
    ronin.SetValue(1, pan); // Canale 1 → Pan
    ronin.SetValue(2, tilt); // Canale 2 → Tilt

    // Aggiorna e invia il frame S.Bus
    ronin.Update();
    ronin.Send();

    // Piccola pausa per evitare di saturare la comunicazione S.Bus
    delay(sbusWAIT);
  }
}
