# DP-Week1 Task 1 - Balatro-Like Core Loop

## Nama Kelompok
Gea Ismawianda Aulia Firdausy - 5225600117  
Rizky Eka Aji Santoso - 5225600119  
Shelen ahmad kahfi - 5225600104  
Kalvin Luna Sinuraya - 5225600120  
I Putu Satwika Werdi Widagda Karang - 5225600112  
Ignatius Davin Keane Souisa - 5225600092  
Moch Salman Al Fariz - 5225600107  

## Reflection

**1. What is the invariant structure in your program?**
Struktur invariant dalam program ini adalah alur eksekusi fase permainan di dalam kelas `RunSession`[cite: 1, 2]. Urutan 6 fase tersebut mencakup pembuatan input, perhitungan skor dasar, perhitungan reward, pembaruan jumlah uang, fase toko, dan perpindahan ronde[cite: 1, 2]. Urutan ini bersifat permanen dan tidak boleh diubah atau diselingi oleh logika luar[cite: 2, 5].

**2. Which parts are mutable?**
Bagian yang bersifat mutable adalah implementasi spesifik dari setiap modul pendukung[cite: 1, 2]. Hal ini mencakup algoritma pembuatan input pada `IInputGenerator`, aturan kalkulasi poin pada `IScoringRule`, formula perolehan uang pada `IRewardRule`, serta item penawaran pada `ShopSystem`[cite: 2]. Seluruh logika internal komponen tersebut dapat diubah atau diganti tanpa memengaruhi urutan fase[cite: 1, 4].

**3. When you replaced the InputGenerator, why didn't RunSession change?**
Kelas `RunSession` tidak mengalami perubahan karena menerapkan prinsip abstraksi melalui antarmuka `IInputGenerator`[cite: 2]. `RunSession` hanya bergantung pada kontrak metode abstrak `generateInput()`, bukan pada kelas konkret tertentu[cite: 2]. Saat `FixedInputGenerator` diganti dengan `RandomInputGenerator`, `RunSession` tetap memanggil metode yang sama tanpa perlu mengetahui bagaimana input acak dihasilkan di dalamnya[cite: 4, 5].

**4. What would happen if scoring logic was placed inside RunSession?**
Jika logika kalkulasi skor diletakkan di dalam kelas `RunSession`, maka struktur invariant akan rusak[cite: 2, 5]. `RunSession` menjadi terikat secara langsung pada aturan permainan spesifik, sehingga setiap kali ada perubahan cara menghitung skor, kode di dalam `RunSession` harus dimodifikasi[cite: 2, 5]. Hal ini melanggar pemisahan tanggung jawab dan membuat arsitektur sistem menjadi kaku[cite: 1, 5].
