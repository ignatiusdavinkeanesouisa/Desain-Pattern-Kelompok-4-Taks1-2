#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Struct data untuk aksi pemain dan status combat
struct PlayerAction {
    std::string actionName;
    int baseDamage;
};

struct CombatResult {
    bool isHit;
    int damageDealt;
    bool enemyDefeated;
};

// --- ABSTRAKSI (INTERFACES) ---

class IPlayerController {
public:
    virtual ~IPlayerController() = default;
    virtual PlayerAction getPlayerAction() = 0;
};

class ICombatResolver {
public:
    virtual ~ICombatResolver() = default;
    virtual CombatResult resolveCombat(const PlayerAction& action) = 0;
};

class IRewardSystem {
public:
    virtual ~IRewardSystem() = default;
    virtual int calculateReward(const CombatResult& result) = 0;
};

// --- IMPLEMENTASI KONKRET (MUTABLE BEHAVIOR) ---

class BasicPlayerController : public IPlayerController {
public:
    PlayerAction getPlayerAction() override {
        return PlayerAction{"Slash Attack", 15};
    }
};

class StandardCombatResolver : public ICombatResolver {
public:
    CombatResult resolveCombat(const PlayerAction& action) override {
        // Simulasi kalkulasi damage
        int finalDamage = action.baseDamage + (std::rand() % 10);
        bool defeated = finalDamage > 18;
        return CombatResult{true, finalDamage, defeated};
    }
};

class WaveRewardSystem : public IRewardSystem {
public:
    int calculateReward(const CombatResult& result) override {
        if (result.enemyDefeated) {
            return 50; // Reward gold jika musuh kalah
        }
        return 10; // Reward partisipasi
    }
};

// --- GAME SESSION (INVARIANT CORE LOOP) ---

class GameSession {
private:
    IPlayerController& playerController;
    ICombatResolver& combatResolver;
    IRewardSystem& rewardSystem;
    
    int playerHP;
    int playerGold;
    int currentWave;
    const int maxWaves;
    bool gameOver;

public:
    GameSession(IPlayerController& pc, ICombatResolver& cr, IRewardSystem& rs)
        : playerController(pc), combatResolver(cr), rewardSystem(rs),
          playerHP(100), playerGold(0), currentWave(1), maxWaves(3), gameOver(false) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    bool isGameOver() const {
        return gameOver || currentWave > maxWaves;
    }

    void runLoop() {
        std::cout << "=== GAME START (Wave Survival) ===\n\n";

        while (!isGameOver()) {
            std::cout << "--- Wave " << currentWave << " ---\n";

            // Step 1: Player Action
            PlayerAction action = playerController.getPlayerAction();
            std::cout << "[ACTION] Player uses: " << action.actionName << "\n";

            // Step 2: System Evaluates Combat
            CombatResult result = combatResolver.resolveCombat(action);
            std::cout << "[COMBAT] Hit for " << result.damageDealt << " damage!";
            if (result.enemyDefeated) {
                std::cout << " (Enemy Defeated)";
            }
            std::cout << "\n";

            // Step 3: Reward / Penalty Evaluation
            int goldGained = rewardSystem.calculateReward(result);
            playerGold += goldGained;
            std::cout << "[REWARD] Gained " << goldGained << " Gold. Total Gold: " << playerGold << "\n";

            // Step 4: Game State Update & Condition Check
            if (result.enemyDefeated) {
                std::cout << "[STATE] Wave cleared successfully.\n";
                currentWave++;
            } else {
                playerHP -= 15; // Penalty HP jika musuh belum kalah
                std::cout << "[STATE] Enemy counter-attacked! Player HP: " << playerHP << "\n";
                if (playerHP <= 0) {
                    gameOver = true;
                    std::cout << "[STATE] Player defeated!\n";
                }
            }

            std::cout << "\n";
        }

        std::cout << "=== GAME OVER ===\n";
        std::cout << "Final Status -> Waves Cleared: " << (currentWave - 1) 
                  << " | Final Gold: " << playerGold << "\n";
    }
};

// --- MAIN FUNCTION ---

int main() {
    BasicPlayerController playerCtrl;
    StandardCombatResolver combatRes;
    WaveRewardSystem rewardSys;

    // Menjalankan GameSession tanpa menulis logika game di main()
    GameSession session(playerCtrl, combatRes, rewardSys);
    session.runLoop();

    return 0;
}