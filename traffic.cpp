// Inisialisasi Variable
int ITERATION = 0;
const int PIN_MERAH = 2;
const int PIN_KUNING = 3;
const int PIN_HIJAU = 4;

void setup()
{
  for(int i=2;i<=13;i++){		// Pengulangan untuk setup seluruh pin
    pinMode(i, OUTPUT);			// ke mode Output.
  }
  defaultState();				// Memanggil function defaultState().
  delay(1000);
}

/*
	defaultState() menyalakan seluruh LED merah sebelum memulai looping simpangan.
    Cara menemukan pin dengan LED merah dengan mencari i yang menghasilkan sisa bagi
    sama dengan 2.
*/
void defaultState()
{
  for(int i=2; i<=13;i++) {		// Pengulangan untuk menghidupkan seluruh
    if(i%3==2) {				// LED berwarna merah.
      digitalWrite(i, HIGH);
    }
  }
}

/*
	blink() akan menerima argumen berupa pin LED lalu melemparnya ke dalam pengulangan
    untuk mengedipkan LED tersebut sebanyak 3 kali.
*/
void blink(int LED)
{
  for(int i=0;i<3;i++){			// Pengulangan untuk mengedipkan lampu LED
    digitalWrite(LED, HIGH);	// sebanyak 3 kali.
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
}

/*
	simpanganAktif() akan mengaktifkan salah satu simpangan dengan menerima tiga argumen
    pin LED berupa merah, kuning, dan hijau.
*/
void simpanganAktif(int LED_MERAH, int LED_KUNING, int LED_HIJAU)
{
  digitalWrite(LED_MERAH, LOW);		// Mematikan LED merah.
  blink(LED_KUNING);				// Memanggil function blink dengan param LED kuning.
  digitalWrite(LED_KUNING, HIGH);	// Menyalakan LED kuning selama 2 detik.
  delay(2000);
  digitalWrite(LED_KUNING, LOW);	// Mematikan LED kuning dan menyalakan LED hijau
  digitalWrite(LED_HIJAU, HIGH);	// selama 5 detik.
  delay(5000);
  digitalWrite(LED_HIJAU, LOW);		// Mematikan LED hijau dan menyalakan kembali LED
  digitalWrite(LED_MERAH, HIGH);	// merah.
}

void loop()
{
/*
	Untuk menemukan ketiga pin LED dari salah satu simpangan, kita dapat mengambil nomor pin
    dari simpangan pertama lalu ditambahkan dengan jarak antar pin dengan warna yang sama dikali
    dengan iterasi.
*/
  int LED_MERAH = PIN_MERAH + 3 * ITERATION;
  int LED_KUNING = PIN_KUNING + 3 * ITERATION;
  int LED_HIJAU = PIN_HIJAU + 3 * ITERATION;
  
  if(ITERATION < 4) {									// Kondisi apabila iterasi kurang dari 4
    simpanganAktif(LED_MERAH, LED_KUNING, LED_HIJAU);	// maka panggil function simpanganAktif
    delay(1000);										// dengan param LED merah, kuning, dan hijau
    ITERATION++;										// lalu incrementkan nilai ITERATION.
  } else {
    ITERATION = 0;										// reset iterasi agar kembali ke simpangan utara.
  }
  
}