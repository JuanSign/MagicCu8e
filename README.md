# 🌈✨ MagicCu8e ✨🎲

Repository ini berisi implementasi algoritma *local search* untuk memecahkan permasalahan **Diagonal Magic Cube** dengan berbagai pendekatan, termasuk *hill-climbing*, *simulated annealing*, dan *genetic algorithm*. Diagonal Magic Cube adalah kubus yang terdiri dari angka-angka yang disusun sedemikian rupa sehingga jumlahnya pada berbagai komponen (baris, kolom, diagonal) mencapai nilai konstan yang disebut *magic number*. Project ini merupakan tugas besar yang dilakukan oleh tim untuk mata kuliah **Dasar Inteligensi Artifisial** di Institut Teknologi Bandung.


          +-----------------------+
         /                       /|
        /                       / |
       /                       /  |
      +-----------------------+   |
      |                       |   |
      |                       |   |
      |                       |   |
      |                       |   |
      |                       |   +
      |                       |  /
      |                       | /
      |                       |/
      +-----------------------+


## Deskripsi Singkat

MagicCu8e bertujuan untuk membangun dan mengoptimalkan konfigurasi **magic cube** berukuran 5x5x5 dengan menggunakan beberapa teknik *local search*. Setiap algoritma akan mencoba mengonfigurasi kubus sehingga seluruh *constraint* (baris, kolom, tiang, dan diagonal) memiliki jumlah yang sama dengan *magic number* (315), sesuai dengan aturan dalam penyusunan magic cube.

## Struktur Direktori

- **src/main.cpp**: Fungsi utama untuk menjalankan program.
- **src/algorithms/**: Direktori yang berisi implementasi berbagai algoritma:
  - **genetic-algorithm/GA.cpp**: Implementasi *genetic algorithm*.
  - **hill-climbings/HCSA.cpp**: Implementasi *hill-climbing steepest ascent*.
  - **simulated-annealing/SA.cpp**: Implementasi *simulated annealing*.
- **src/cube/CUBE.cpp**: Kelas utama untuk mendefinisikan struktur kubus dan operasinya.
- **src/functions/**: Fungsi-fungsi penunjang dalam algoritma:
  - **fitness-function/FITNESS-FUNCTION.cpp**: Menghitung nilai *fitness* dari konfigurasi kubus.
  - **objective-function/OBJECTIVE-FUNCTION.cpp**: Tiga opsi fungsi objektif yang digunakan dalam evaluasi.
  - **scheduling-function/SCHEDULING-FUNCTION.cpp**: Fungsi penjadwalan untuk algoritma *simulated annealing*.

## Cara Setup dan Menjalankan Program

### Persyaratan
Pastikan Anda memiliki **g++** terpasang pada sistem Anda. Berikut adalah cara untuk mengompilasi dan menjalankan program dari terminal:

1. Clone repository ini ke dalam direktori lokal Anda:
   ```bash
   git clone https://github.com/JuanSign/MagicCu8e.git

2. Navigasikan ke direktori repository:
   ```bash
   cd MagicCu8e

3. Kompilasi program dengan menggunakan perintah berikut:
   ```bash
   g++ src/main.cpp src/algorithms/genetic-algorithm/GA.cpp src/algorithms/hill-climbings/HCSA.cpp src/algorithms/simulated-annealing/SA.cpp src/cube/CUBE.cpp src/functions/fitness-function/FITNESS-FUNCTION.cpp src/functions/objective-function/OBJECTIVE-FUNCTION.cpp src/functions/scheduling-function/SCHEDULING-FUNCTION.cpp .\src\algorithms\hill-climbings\HCS.cpp .\src\algorithms\hill-climbings\HCSM.cpp -o main

4. Jalankan program:
   ```bash
   ./main


### Opsi Algoritma
Program ini mendukung tiga algoritma utama untuk menyelesaikan *Diagonal Magic Cube*:
- **Hill-Climbing Steepest Ascent**: Algoritma ini bekerja dengan mencari nilai terbaik pada setiap langkah pergerakan di sekitar titik saat ini dan memilih langkah yang menghasilkan perbaikan terbesar. Dalam konteks ini, algoritma akan berusaha meminimalkan selisih atau memaksimalkan jumlah *constraint* yang terpenuhi dalam setiap langkahnya.
  
- **Simulated Annealing**: Algoritma ini mirip dengan *hill-climbing* namun dengan kemampuan untuk menerima solusi yang kurang optimal pada tahap awal, dengan tujuan menghindari jebakan di solusi lokal. Semakin lama proses berjalan, algoritma akan semakin ketat dalam menerima solusi yang kurang optimal, hingga akhirnya fokus hanya pada solusi terbaik.

- **Genetic Algorithm**: Algoritma ini menggunakan pendekatan populasi dan seleksi alam. Setiap generasi akan memilih individu terbaik berdasarkan *fitness function*, melakukan mutasi, dan menghasilkan generasi baru yang lebih optimal. Algoritma ini cocok untuk eksplorasi ruang solusi yang lebih luas.

Setiap algoritma menggunakan metode optimasi yang berbeda dalam memenuhi *constraint* magic cube. Anda dapat memilih algoritma yang ingin digunakan dengan menyetel parameter pada `main.cpp` sesuai kebutuhan Anda.

## Pembagian Tugas Anggota Kelompok

| Nama                          | NIM       | Tugas                                                                                   |
|-------------------------------|-----------|-----------------------------------------------------------------------------------------|
| Akmal Galih Aji Sugmo Seno    | 18222046  | Menganalisis dan menjelaskan implementasi algoritma, Mengimplementasikan algoritma Hill-Climbing |
| Firsa Athaya Raissa Alifah    | 18222051  | Menentukan fungsi objektif, Mengimplementasikan algoritma kubus                         |
| Athhar Mahendra Umar          | 18222080  | Menganalisis hasil eksperimen, Mengimplementasikan algoritma Simulated Annealing        |
| Juan Sohuturon Arauna Siagian | 18222086  | Menentukan algoritma terbaik untuk Diagonal Magic Cube, Mengimplementasikan algoritma Genetic Algorithm |

