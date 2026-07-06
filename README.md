# Tebak Kata - Edisi Robotika

Implementasi game Hangman berbasis command-line interface yang ditulis sepenuhnya menggunakan bahasa C. Proyek ini mendemonstrasikan manipulasi pointer, struktur data berlapis, serta algoritma searching dan sorting secara langsung di memori.

## Cara Kompilasi dan Menjalankan

Program ini tidak membutuhkan dependensi eksternal. Gunakan compiler GCC standar dan tambahkan flag warning untuk memastikan eksekusi berjalan aman.

```bash
gcc -Wall -o tebak_kata tebak_kata.c
./tebak_kata
```

## Daftar Fitur

Permainan ini memproses input pemain karakter demi karakter dengan perlindungan terhadap input buffer sisa, sehingga antarmuka terminal tetap rapi dan tidak mengalami infinite loop saat menerima masukan yang salah. Terdapat visualisasi ASCII art yang diperbarui setiap kali pemain salah menebak huruf. 

Di luar siklus permainan utama, sistem dilengkapi dengan papan peringkat yang diurutkan secara otomatis dari skor tertinggi menggunakan algoritma bubble sort. Tersedia juga fitur ekspansi bank kata tempat pemain bisa memasukkan kosakata baru. Kata-kata baru ini divalidasi keberadaannya menggunakan pencarian biner, lalu disisipkan ke memori menggunakan logika pergeseran array agar urutan alfabetis selalu terjaga tanpa perlu melakukan sorting ulang.

## Keterbatasan yang Diketahui

Penyimpanan skor dan penambahan kata hanya bersifat sementara di dalam RAM karena tidak ada implementasi sistem file I/O. Seluruh rekor dan kosakata baru akan hilang begitu eksekusi program dihentikan. 

Selain itu, alokasi memori dinamis pada bank kata saat menambahkan kata baru bercampur dengan memori statis bawaan string literal kompilator. Mengingat skalanya hanya untuk keperluan demonstrasi praktikum, pembebasan memori secara total pada akhir sesi belum diimplementasikan karena dapat memicu segmentasi jika fungsi free() salah menyentuh memori statis.

## Dokumentasi Alur Logika

Untuk memahami lebih dalam bagaimana state machine permainan ini bekerja, seluruh diagram teknis sudah dipisahkan ke dalam direktori `/docs`. 

- [Klik di sini untuk melihat dokumentasi alur menu utama](./docs/menu-utama.svg)
- [Klik di sini untuk melihat dokumentasi logika satu kali tebakan](./docs/proses-tebakan.svg)
- [Klik di sini untuk melihat dokumentasi algoritma penambahan kata dan pencarian biner](./docs/tambah-kata.svg)
