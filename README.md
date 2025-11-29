# Property Data Manager CLI 🏠
Aplikasi manajemen data properti berbasis CLI menggunakan bahasa C. Memiliki fitur pencarian (Linear Search), pengurutan data tingkat lanjut (Merge Sort), dan manipulasi file CSV

![Language](https://img.shields.io/badge/Language-C-blue)
![Algorithm](https://img.shields.io/badge/Algorithm-MergeSort-green)
![Status](https://img.shields.io/badge/Status-Completed-success)

Aplikasi berbasis **Command Line Interface (CLI)** yang ditulis dalam bahasa C untuk mengelola, mencari, dan mengurutkan ribuan data properti perumahan. Program ini dirancang untuk menangani dataset CSV dalam jumlah besar (hingga 4000+ baris) dengan efisiensi menggunakan algoritma sorting yang optimal.

## 🌟 Fitur Utama

* **Read Data**: Membaca data properti secara otomatis dari file CSV (`file.csv`).
* **Display Data**: Menampilkan data dalam format tabel yang rapi.
* **Advanced Sorting (Merge Sort)**:
    * Mengurutkan data berdasarkan berbagai kategori (Harga, Lokasi, Jumlah Kamar, dll).
    * Mendukung pengurutan secara **Ascending** (naik) dan **Descending** (turun).
    * Menggunakan algoritma *Merge Sort* (`O(n log n)`) untuk performa yang stabil.
* **Smart Search**:
    * Mencari data spesifik berdasarkan lokasi, kota, harga, tipe, atau furnitur.
    * Menangani input huruf besar/kecil (case-insensitive) secara otomatis.
* **Export Data**: Menyimpan hasil data yang telah diurutkan atau dimodifikasi ke file CSV baru.

## 📂 Struktur Data

Program ini memproses data dengan atribut berikut:
* Location (Lokasi Spesifik)
* City (Kota)
* Price (Harga)
* Rooms (Jumlah Kamar Tidur)
* Bathrooms (Jumlah Kamar Mandi)
* Car Parks (Kapasitas Parkir)
* Type (Tipe Properti: Built-up / Land-area)
* Furnish (Kondisi Perabotan)

## 🛠️ Cara Menjalankan Program

### Prasyarat
Pastikan kamu sudah menginstall Compiler C (seperti GCC).

### Langkah-langkah
1.  **Clone repository ini:**
    ```bash
    git clone [https://github.com/gabrielle-jeco/Property-Data-Manager-CLI.git](https://github.com/gabrielle-jeco/Property-Data-Manager-CLI.git)
    ```
2.  **Siapkan File Data:**
    Pastikan file `file.csv` berada dalam satu folder dengan kode program. Format header CSV harus sesuai dengan struktur data program.
3.  **Compile Program:**
    ```bash
    gcc aol2.c -o property_app
    ```
4.  **Jalankan Program:**
    * Windows:
        ```bash
        property_app.exe
        ```
    * Linux/Mac:
        ```bash
        ./property_app
        ```

## 🧩 Penjelasan Teknis

### Algoritma Sorting
Program ini menggunakan **Merge Sort** karena stabilitas dan efisiensinya dalam menangani array of struct yang besar. Fungsi sorting dibuat modular sehingga user dapat memilih kolom mana yang ingin diurutkan dan jenis pengurutannya (ASC/DESC).

### Input Handling
Program dilengkapi dengan error handling dasar untuk input menu dan validasi string (seperti mengubah input user menjadi format yang sesuai sebelum dibandingkan dengan data).
