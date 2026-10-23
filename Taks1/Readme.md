# DP-Week1 Task 1 - Balatro-Like Core Loop

## Reflection

**1. What is the invariant structure in your program?**
Struktur invariant dalam program ini adalah alur eksekusi fase permainan di dalam kelas `RunSession`[cite: 1, 2]. Urutan 6 fase tersebut mencakup pembuatan input, perhitungan skor dasar, perhitungan reward, pembaruan jumlah uang, fase toko, dan perpindahan ronde[cite: 1, 2]. Urutan ini bersifat permanen dan tidak boleh diubah atau diselingi oleh logika luar[cite: 2, 5].

**2. Which parts are mutable?**
Bagian yang bersifat mutable adalah implementasi spesifik dari setiap modul pendukung[cite: 1, 2]. Hal ini mencakup algoritma pembuatan input pada `IInputGenerator`, aturan kalkulasi poin pada `IScoringRule`, formula perolehan uang pada `IRewardRule`, serta item penawaran pada `ShopSystem`[cite: 2]. Seluruh logika internal komponen tersebut dapat diubah atau diganti tanpa memengaruhi urutan fase[cite: 1, 4].

**3. When you replaced the InputGenerator, why didn't RunSession change?**
Kelas `RunSession` tidak mengalami perubahan karena menerapkan prinsip abstraksi melalui antarmuka `IInputGenerator`[cite: 2]. `RunSession` hanya bergantung pada kontrak metode abstrak `generateInput()`, bukan pada kelas konkret tertentu[cite: 2]. Saat `FixedInputGenerator` diganti dengan `RandomInputGenerator`, `RunSession` tetap memanggil metode yang sama tanpa perlu mengetahui bagaimana input acak dihasilkan di dalamnya[cite: 4, 5].

**4. What would happen if scoring logic was placed inside RunSession?**
Jika logika kalkulasi skor diletakkan di dalam kelas `RunSession`, maka struktur invariant akan rusak[cite: 2, 5]. `RunSession` menjadi terikat secara langsung pada aturan permainan spesifik, sehingga setiap kali ada perubahan cara menghitung skor, kode di dalam `RunSession` harus dimodifikasi[cite: 2, 5]. Hal ini melanggar pemisahan tanggung jawab dan membuat arsitektur sistem menjadi kaku[cite: 1, 5].

DP-Week1 Task 1 - Balatro-Like Core Loop

Dokumentasi ini berisi penjelasan mengenai arsitektur sistem permainan berbasis Core Loop Balatro dan jawaban refleksi konseptual.

Refleksi Arsitektur (Reflection)

1. Apakah struktur invariant dalam program ini?
Struktur invariant dalam program ini adalah urutan eksekusi fase permainan yang terikat di dalam kelas RunSession. Urutan ini terdiri dari 6 fase kaku yang harus berjalan secara berurutan:

- Generate input (Penerimaan input)
- Compute base score (Kalkulasi skor dasar)
- Compute reward (Kalkulasi hadiah)
- Update money (Pembaruan total uang)
- Shop phase (Fase toko)
- Advance round (Pindah ke ronde berikutnya)

Urutan ini bersifat permanen dan tidak boleh diubah, diselingi, atau diabaikan oleh komponen luar.

2. Bagian mana saja yang bersifat mutable?
Bagian yang bersifat mutable adalah logika spesifik dan aturan perhitungan yang diimplementasikan oleh modul-modul pendukung di luar RunSession, yaitu:

- Algoritma pembuatan input pada IInputGenerator (misalnya input tetap vs input acak).
- Aturan kalkulasi skor pada IScoringRule.
- Rumus penentuan imbalan uang pada IRewardRule.
- Daftar item atau penawaran pada ShopSystem.

Seluruh komponen ini dapat diubah, diganti, atau dimodifikasi perilakunya tanpa memengaruhi alur eksekusi utama.

3. Ketika InputGenerator diganti, mengapa kelas RunSession tidak ikut berubah?
Kelas RunSession tidak mengalami perubahan karena menerapkan prinsip abstraksi (interface) melalui IInputGenerator. RunSession hanya bergantung pada kontrak metode generateInput() yang disediakan oleh interface, bukan pada kelas konkret tertentu.

Ketika FixedInputGenerator diganti dengan RandomInputGenerator, RunSession tetap memanggil metode yang sama tanpa perlu mengetahui bagaimana proses internal pembuatan angka acak tersebut dilakukan.

4. Apa yang akan terjadi jika logika kalkulasi skor diletakkan di dalam kelas RunSession?
Jika logika kalkulasi skor dimasukkan langsung ke dalam kelas RunSession, maka:

- Prinsip Invariant Rusak: RunSession menjadi terikat erat (tightly coupled) dengan aturan permainan spesifik.
- Pelanggaran Single Responsibility Principle (SRP): RunSession yang seharusnya hanya mengatur alur siklus permainan kini juga bertanggung jawab atas perhitungan matematika skor.
- Kode Menjadi Kaku: Setiap kali ada perubahan aturan skor (misalnya efek item atau kalkulasi bonus), kita terpaksa harus mengubah kode di dalam RunSession, yang berisiko merusak alur utama permainan.
