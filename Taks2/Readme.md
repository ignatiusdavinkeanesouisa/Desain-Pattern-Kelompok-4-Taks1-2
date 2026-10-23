# DP-Week2 Task 2 - Core Loop Architecture

## Nama Kelompok
Gea Ismawianda Aulia Firdausy - 5225600117  
Rizky Eka Aji Santoso - 5225600119  
Shelen ahmad kahfi - 5225600104  
Kalvin Luna Sinuraya - 5225600120  
I Putu Satwika Werdi Widagda Karang - 5225600112  
Ignatius Davin Keane Souisa - 5225600092  
Moch Salman Al Fariz - 5225600107  

## Step 1: Core Loop Description
Game concept: Wave Survival Action / Combat Dungeon.
1. Player selects and performs an action (Attack/Skill).
2. System evaluates combat interaction and calculates damage output.
3. System determines reward (Gold) or penalty (HP loss) based on combat result.
4. System updates player stats (HP, Gold) and wave progress state.
5. System checks win/lose conditions and advances to the next wave or ends the session.

## Step 2: Invariant Elements
1. **Phase Order**: Sequential execution of Input -> Combat Resolution -> Reward Calculation -> State Update -> Wave Advancement.
2. **Core Components**: Interface abstraction (`IPlayerController`, `ICombatResolver`, `IRewardSystem`) and session manager (`GameSession`).
3. **Pipeline Breakdown Risk**: If the order changes (e.g., calculating reward before combat resolution), player rewards will be evaluated based on uncalculated or stale combat states.

## Step 3: Mutable Elements
1. **Damage Formula & Multipliers**: The mathematical formula for damage calculation in `ICombatResolver` can change based on weapon types or player buffs.
2. **Reward Scaling System**: The amount of Gold distributed by `IRewardSystem` can scale dynamically depending on difficulty settings.
3. **Enemy AI & Encounter Spawns**: The type and behavior of enemies encountered per wave can be altered.
*Reasoning*: These elements represent parameters and behavioral content. They can be modified, replaced, or expanded without altering the execution sequence of `GameSession`.

---

## Reflection

### 1. What is the invariant structure of your game?
Invariant structure dalam game ini adalah alur eksekusi fase pada kelas `GameSession`. Urutan fase tersebut diawali dari penerimaan input pemain, dilanjutkan dengan evaluasi sistem pertarungan, kalkulasi imbalan atau penalti, pembaruan status pemain, hingga pemeriksaan kondisi selesai giliran. Selain urutan eksekusi, kontrak antarmuka abstrak `IPlayerController`, `ICombatResolver`, dan `IRewardSystem` juga bersifat invariant karena menjadi fondasi komunikasi antar modul yang tidak boleh diubah struktur dasarnya.

### 2. What parts are mutable?
Bagian yang bersifat mutable adalah logika internal dan nilai parameter di dalam kelas-kelas konkret yang mengimplementasikan interface. Contohnya adalah algoritma penentuan besaran kerusakan pada pertarungan, persentase kemungkinan serangan meleset, formula pemberian imbalan koin emas, serta variasi tipe aksi yang dimiliki oleh pemain. Seluruh komponen ini dapat diubah, ditambah, atau disesuaikan nilainya tanpa mengganggu jalannya alur utama program.

### 3. If you wanted to add a new feature, which class would change?
Jika saya ingin menambahkan fitur baru seperti sistem serangan kritis atau item peningkat status (*buff*), saya hanya perlu membuat kelas konkret baru yang mengimplementasikan `ICombatResolver` atau `IPlayerController` tanpa mengubah kelas `GameSession`. Misalnya, membuat `CriticalCombatResolver` untuk menangani perhitungan kerusakan kritis. Pendekatan ini menjaga alur utama tetap bersih dari perubahan fitur spesifik.

### 4. If you changed the loop order, what would break?
Mengubah urutan *loop* akan merusak logika dasar permainan. Jika fase pembaruan status dijalankan sebelum fase kalkulasi pertarungan, nilai kesehatan pemain (*HP*) atau status musuh akan diperbarui berdasarkan data yang belum dihitung. Begitu pula jika fase pemberian imbalan dilakukan sebelum pertarungan selesai dievaluasi, sistem dapat memberikan hadiah secara tidak sah sebelum hasil aksi pemain terkonfirmasi.
