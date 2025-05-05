#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// Класс для представления кандидата
class Candidate {
public:
    string name;
    int borda_score;
    
    Candidate(const string& n) : name(n), borda_score(0) {}
};

// Класс для представления избирателя
class Voter {
public:
    vector<string> preferences;
    
    Voter(const vector<string>& pref) : preferences(pref) {}
};

// Класс для проведения выборов
class Election {
private:
    vector<Candidate> candidates;
    vector<Voter> voters;
    
public:
    // Добавление кандидата
    void addCandidate(const string& name) {
        candidates.emplace_back(name);
    }
    
    // Добавление избирателя
    void addVoter(const vector<string>& preferences) {
        voters.emplace_back(preferences);
    }
    
    // Метод Борда
    string calculateBordaWinner() {
        // Сброс счетчиков
        for (auto& c : candidates) {
            c.borda_score = 0;
        }
        
        // Начисление баллов
        for (const auto& voter : voters) {
            for (size_t i = 0; i < voter.preferences.size(); ++i) {
                int points = voter.preferences.size() - i - 1;
                for (auto& c : candidates) {
                    if (c.name == voter.preferences[i]) {
                        c.borda_score += points;
                        break;
                    }
                }
            }
        }
        
        // Поиск победителя
        int max_score = -1;
        string winner;
        for (const auto& c : candidates) {
            if (c.borda_score > max_score) {
                max_score = c.borda_score;
                winner = c.name;
            }
        }
        
        return winner;
    }
    
    // Метод Кондорсе
    string calculateCondorcetWinner() {
        map<string, map<string, int>> pairwise_results;
        
        // Инициализация матрицы попарных сравнений
        for (const auto& c1 : candidates) {
            for (const auto& c2 : candidates) {
                if (c1.name != c2.name) {
                    pairwise_results[c1.name][c2.name] = 0;
                }
            }
        }
        
        // Заполнение матрицы попарных сравнений
        for (const auto& voter : voters) {
            for (size_t i = 0; i < voter.preferences.size(); ++i) {
                for (size_t j = i + 1; j < voter.preferences.size(); ++j) {
                    string preferred = voter.preferences[i];
                    string other = voter.preferences[j];
                    pairwise_results[preferred][other]++;
                }
            }
        }
        
        // Поиск победителя Кондорсе
        for (const auto& c1 : candidates) {
            bool is_condorcet_winner = true;
            
            for (const auto& c2 : candidates) {
                if (c1.name != c2.name) {
                    if (pairwise_results[c1.name][c2.name] <= pairwise_results[c2.name][c1.name]) {
                        is_condorcet_winner = false;
                        break;
                    }
                }
            }
            
            if (is_condorcet_winner) {
                return c1.name;
            }
        }
        
        return "Нет победителя по Кондорсе";
    }
};

int main() {
    Election election;
    
    // Пример 1: Простой случай с явным победителем
    {
        election.addCandidate("Петя");
        election.addCandidate("Вася");
        election.addCandidate("Оля");
        
        // 2 избирателя предпочитают: Вася > Оля > Петя
        election.addVoter({"Вася", "Оля", "Петя"});
        election.addVoter({"Вася", "Оля", "Петя"});
        
        // 1 избиратель предпочитает: Оля > Вася > Петя
        election.addVoter({"Оля", "Вася", "Петя"});
        
        string borda_winner = election.calculateBordaWinner();
        string condorcet_winner = election.calculateCondorcetWinner();
        
        cout << "Пример 1:\n";
        cout << "Победитель по Борда: " << borda_winner << endl;
        cout << "Победитель по Кондорсе: " << condorcet_winner << endl;
        
        if (borda_winner != condorcet_winner) {
            cout << "Замечание: разные методы дали разных победителей!\n";
        }
        cout << "------------------------\n";
    }
    
    // Пример 2: Парадокс Кондорсе (разные победители)
    {
        Election paradox_election;
        paradox_election.addCandidate("A");
        paradox_election.addCandidate("B");
        paradox_election.addCandidate("C");
        
        // Голоса, создающие парадокс Кондорсе
        paradox_election.addVoter({"A", "B", "C"});
        paradox_election.addVoter({"B", "C", "A"});
        paradox_election.addVoter({"C", "A", "B"});
        
        string borda_winner = paradox_election.calculateBordaWinner();
        string condorcet_winner = paradox_election.calculateCondorcetWinner();
        
        cout << "Пример 2 (Парадокс Кондорсе):\n";
        cout << "Победитель по Борда: " << borda_winner << endl;
        cout << "Победитель по Кондорсе: " << condorcet_winner << endl;
        
        if (borda_winner != condorcet_winner) {
            cout << "Замечание: разные методы дали разных победителей!\n";
            cout << "Это демонстрирует парадокс Кондорсе, когда нет победителя по Кондорсе,\n";
            cout << "но метод Борда дает определенного победителя.\n";
        }
        cout << "------------------------\n";
    }
    
    // Пример 3: Все избиратели имеют одинаковые предпочтения
    {
        Election unanimous_election;
        unanimous_election.addCandidate("X");
        unanimous_election.addCandidate("Y");
        unanimous_election.addCandidate("Z");
        
        // Все избиратели предпочитают: X > Y > Z
        for (int i = 0; i < 5; ++i) {
            unanimous_election.addVoter({"X", "Y", "Z"});
        }
        
        string borda_winner = unanimous_election.calculateBordaWinner();
        string condorcet_winner = unanimous_election.calculateCondorcetWinner();
        
        cout << "Пример 3 (Единогласное голосование):\n";
        cout << "Победитель по Борда: " << borda_winner << endl;
        cout << "Победитель по Кондорсе: " << condorcet_winner << endl;
        
        if (borda_winner != condorcet_winner) {
            cout << "Замечание: разные методы дали разных победителей!\n";
        } else {
            cout << "Оба метода согласны с победителем.\n";
        }
        cout << "------------------------\n";
    }
    
    return 0;
}
