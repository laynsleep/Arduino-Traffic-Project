//	INISIALISASI VARIABEL
int BUTTON_PIN = 2;
int PASSERBY_TRAFFIC_PINS[4] = {3, 4, 9, 8};
int STREET_TRAFFIC_PINS[3] = {5, 6, 7};
int BUTTON_STATE;

void setup() {
  for(int i=3; i <= 9; i++) {	// Pengulangan untuk set pin 3-9 ke OUTPUT
    pinMode(i, OUTPUT);
  }
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);	// Set pin 2 (button) ke mode INPUT_PULLUP
  
  // Menambahkan interrupt ke pin 2 (button)
  // dan memicu fungsi buttonPressed dengan mode CHANGE
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonPressed, CHANGE);
}

void blink(int LED)
{
  for(int i=0;i<3;i++){			// Pengulangan untuk mengedipkan lampu LED
    digitalWrite(LED, HIGH);	// sebanyak 3 kali
    delay(10000);
    digitalWrite(LED, LOW);
    delay(10000);
  }
}

// Fungsi untuk pergantian lalu lintas pejalan kaki
void pedestrianTrafficState(int active) {
  if(!active) {
    // Jika tidak aktif maka matikan seluruh LED hijau dan nyalakan LED merah
    for(int pin : PASSERBY_TRAFFIC_PINS)
    	(pin % 2 == 0) ? digitalWrite(pin, HIGH) : digitalWrite(pin, LOW);
  } else {
    // Jika aktif nyalakan LED hijau
    for(int pin : PASSERBY_TRAFFIC_PINS)
    	(pin % 3 == 0) ? digitalWrite(pin, HIGH) : digitalWrite(pin, LOW);
  }
}

// Fungsi utama lalu lintas jalan
void streetTrafficState(int active) {
  // Pengulangan untuk mematikan seluruh LED lalu lintas kendaraan
  for(int pin : STREET_TRAFFIC_PINS)
    digitalWrite(pin, LOW);
  
  if(!active) {
    // Jika tidak aktif maka nyalakan LED hijau
    digitalWrite(STREET_TRAFFIC_PINS[0], HIGH);
  } else {
    // Jika aktif matikan fungsi lalu lintas pejalan kaki, nyalakan LED merah
    // lalu menyalakan LED hijau.
	// Setelah jeda, matikan LED merah lalu kedipkan LED kuning 3 kali.
    pedestrianTrafficState(!BUTTON_STATE);
    digitalWrite(STREET_TRAFFIC_PINS[0], LOW);
    digitalWrite(STREET_TRAFFIC_PINS[2], HIGH);
    delay(60000);
    digitalWrite(STREET_TRAFFIC_PINS[2], LOW);
    pedestrianTrafficState(0);
    blink(STREET_TRAFFIC_PINS[1]);
  }
}

// Fungsi interupsi apabila button dipencet
void buttonPressed() {
  int BUTTON_STATE = digitalRead(BUTTON_PIN);	// Membaca nilai dari button (default 1)
  if(!BUTTON_STATE) {
    // Jika button dipencet maka aktifkan lalu lintas utama
    streetTrafficState(!BUTTON_STATE);
  }
}

void loop() {
  // Kondisi awal saat tidak ada interupsi
  pedestrianTrafficState(0);
  streetTrafficState(0);
}