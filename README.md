# Tebak Kata - Edisi Robotika

Implementasi game Hangman berbasis command-line interface yang ditulis sepenuhnya menggunakan bahasa C. Proyek ini mendemonstrasikan manipulasi pointer, struktur data berlapis, serta algoritma searching dan sorting secara langsung di memori.

[![Tonton Video Penjelasan](https://img.youtube.com/vi/ID_VIDEO_YOUTUBE/0.jpg)](https://youtube.com/playlist?list=PLVwDVVjU2I9E&si=MgATMUp1ryYspE45
)

## Cara Kompilasi dan Menjalankan

Program ini tidak membutuhkan dependensi eksternal. Gunakan compiler GCC standar dan tambahkan flag warning untuk memastikan eksekusi berjalan aman.

```bash
vkdltif@asus-expertbook:~$ gcc -Wall -o tebak_kata tebak_kata.c
vkdltif@asus-expertbook:~$ ./tebak_kata
```

## Daftar Fitur

Permainan ini memproses input pemain karakter demi karakter dengan perlindungan terhadap input buffer sisa. Antarmuka terminal akan tetap rapi dan terhindar dari infinite loop saat program menerima masukan yang tidak valid. Terdapat visualisasi ASCII art yang terus diperbarui setiap kali pemain salah menebak huruf. 

Di luar siklus permainan utama, sistem dilengkapi dengan papan peringkat yang diurutkan secara otomatis dari skor tertinggi menggunakan algoritma bubble sort. Tersedia juga fitur ekspansi bank kata tempat pemain bisa memasukkan kosakata baru. Kata-kata baru ini divalidasi keberadaannya menggunakan pencarian biner. Data kemudian disisipkan ke memori menggunakan logika pergeseran array agar urutan alfabetis selalu terjaga tanpa perlu melakukan sorting ulang dari awal.

## Keterbatasan yang Diketahui

Penyimpanan skor dan penambahan kata hanya bersifat sementara di dalam RAM karena tidak ada implementasi sistem file I/O. Seluruh rekor dan kosakata baru akan musnah begitu proses eksekusi program dihentikan. 

Selain itu, alokasi memori dinamis pada bank kata saat menambahkan kata baru bercampur dengan memori statis bawaan string literal kompilator. Pembebasan memori secara total pada akhir sesi sengaja tidak diimplementasikan untuk mencegah segmentasi memori yang bisa terjadi jika fungsi free() secara tidak sengaja dieksekusi pada blok memori statis. Skala program ini memang disesuaikan dengan batasan demonstrasi praktikum.

## Dokumentasi Alur Logika

Untuk memahami bagaimana state machine permainan ini bekerja secara teknis, seluruh diagram alur sudah dipisahkan ke dalam direktori `/docs`. 

- [Klik di sini untuk melihat dokumentasi alur menu utama](./docs/menu-utama.png)
- [Klik di sini untuk melihat dokumentasi logika satu kali tebakan](./docs/proses-tebakan.png)
- [Klik di sini untuk melihat dokumentasi algoritma penambahan kata dan pencarian biner](./docs/tambah-kata.png)
