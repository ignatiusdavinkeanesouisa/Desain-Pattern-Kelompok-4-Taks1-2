#include <iostream>
#include <random>
using namespace std;

// Data input untuk setiap ronde
struct TurnInput {
    int value;
};

// 1. Interface untuk membuat input
class IInputGenerator {
public:
    virtual ~IInputGenerator() = default;
    virtual TurnInput generate() = 0;
};

// Generator awal: selalu menghasilkan angka 3
class FixedInputGenerator : public IInputGenerator {
public:
    TurnInput generate() override {
        return {3};
    }
};

// Generator baru: menghasilkan angka acak 1 sampai 5
class RandomInputGenerator : public IInputGenerator {
private:
    mt19937 rng;
    uniform_int_distribution<int> dist;

public:
    RandomInputGenerator()
        : rng(random_device{}()), dist(1, 5) {}

    TurnInput generate() override {
        return {dist(rng)};
    }
};

// 2. Interface untuk menghitung skor
class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int computeBaseScore(const TurnInput& input) = 0;
};

// Skor dasar sama dengan nilai input
class SimpleScoringRule : public IScoringRule {
public:
    int computeBaseScore(const TurnInput& input) override {
        return input.value;
    }
};

// 3. Interface untuk menghitung reward
class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int computeReward(int baseScore, int roundNumber) = 0;
};

// Aturan reward awal: reward sama dengan skor
class SimpleRewardRule : public IRewardRule {
public:
    int computeReward(int baseScore, int roundNumber) override {
        return baseScore;
    }
};

// Modifikasi reward: skor + 2
class BonusRewardRule : public IRewardRule {
public:
    int computeReward(int baseScore, int roundNumber) override {
        return baseScore + 2;
    }
};

// 4. Sistem toko
class ShopSystem {
public:
    void showOffer() {
        cout << "[SHOP] offered: Bonus(+2) cost 2" << endl;
        cout << "[SHOP] skipped" << endl;
    }
};

// 5. Pengatur alur permainan
class RunSession {
private:
    IInputGenerator& inputGenerator;
    IScoringRule& scoringRule;
    IRewardRule& rewardRule;
    ShopSystem& shop;
    int money = 0;

public:
    RunSession(
        IInputGenerator& generator,
        IScoringRule& scorer,
        IRewardRule& reward,
        ShopSystem& shopSystem
    ) : inputGenerator(generator),
        scoringRule(scorer),
        rewardRule(reward),
        shop(shopSystem) {}

    void run() {
        cout << "=== RUN START ===" << endl;

        for (int round = 1; round <= 3; round++) {
            cout << "\nRound " << round << endl;

            // Phase 1: Generate input
            TurnInput input = inputGenerator.generate();
            cout << "[PLAY] input generated: "
                 << input.value << endl;

            // Phase 2: Compute base score
            int baseScore =
                scoringRule.computeBaseScore(input);
            cout << "[SCORE] base score: "
                 << baseScore << endl;

            // Phase 3: Compute reward
            int reward =
                rewardRule.computeReward(baseScore, round);
            cout << "[REWARD] gain: "
                 << reward << endl;

            // Phase 4: Update money
            money += reward;
            cout << "[MONEY] money: "
                 << money << endl;

            // Phase 5: Shop phase
            shop.showOffer();

            // Phase 6: Advance round
            cout << "[ROUND] advancing to next round"
                 << endl;
        }

        cout << "\n=== RUN END ===" << endl;
        cout << "Final money: " << money << endl;
    }
};

int main() {
    // Modifikasi 1: mengganti generator menjadi random
    RandomInputGenerator inputGenerator;

    SimpleScoringRule scoringRule;

    // Modifikasi 2: reward = base score + 2
    BonusRewardRule rewardRule;

    ShopSystem shop;

    RunSession session(
        inputGenerator,
        scoringRule,
        rewardRule,
        shop
    );

    session.run();

    return 0;
}
