# Tebak Kata - Edisi Robotika

Ini adalah implementasi game tebak kata yang sepenuhnya berjalan di antarmuka command-line (CLI). Proyek ini dibangun sebagai bagian dari tugas akhir praktikum Dasar Pemrograman, sehingga arsitekturnya berfokus pada penerapan konsep fundamental bahasa C seperti manipulasi pointer, struct, serta algoritma searching dan sorting. 

Pemain harus menebak kata rahasia bertema robotika huruf demi huruf sebelum jatah nyawanya habis dan gambar tiang gantungan terbentuk utuh. Selain loop gameplay utama, program ini juga menangani pencatatan skor dalam bentuk papan peringkat dan memungkinkan penambahan kosakata baru secara dinamis ke dalam sistem.

## Cara Menjalankan

Program ini ditulis dalam C murni tanpa dependensi eksternal dan dapat dikompilasi langsung menggunakan GCC. Sangat disarankan untuk menyertakan flag `-Wall` saat proses kompilasi untuk memastikan tidak ada warning yang terlewat.

```bash
gcc -Wall -o tebak_kata tebak_kata.c
./tebak_kata
