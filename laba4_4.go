package main

import (
	"fmt"
	"strings"
)

// Candidate представляет кандидата с его баллами
type Candidate struct {
	Name       string
	BordaScore int
}

// Voter представляет избирателя с его предпочтениями
type Voter struct {
	Preferences []string
}

// Election представляет выборы с кандидатами и избирателями
type Election struct {
	Candidates []Candidate
	Voters     []Voter
}

// AddCandidate добавляет кандидата
func (e *Election) AddCandidate(name string) {
	e.Candidates = append(e.Candidates, Candidate{Name: name})
}

// AddVoter добавляет избирателя
func (e *Election) AddVoter(preferences []string) {
	e.Voters = append(e.Voters, Voter{Preferences: preferences})
}

// CalculateBordaWinner вычисляет победителя по методу Борда
func (e *Election) CalculateBordaWinner() string {
	// Сбрасываем баллы
	for i := range e.Candidates {
		e.Candidates[i].BordaScore = 0
	}

	// Начисляем баллы
	for _, voter := range e.Voters {
		for pos, name := range voter.Preferences {
			for i := range e.Candidates {
				if e.Candidates[i].Name == name {
					e.Candidates[i].BordaScore += len(voter.Preferences) - pos - 1
					break
				}
			}
		}
	}

	// Находим победителя
	maxScore := -1
	winner := ""
	for _, c := range e.Candidates {
		if c.BordaScore > maxScore {
			maxScore = c.BordaScore
			winner = c.Name
		}
	}

	return winner
}

// CalculateCondorcetWinner вычисляет победителя по методу Кондорсе
func (e *Election) CalculateCondorcetWinner() string {
	// Создаем матрицу попарных сравнений
	pairwise := make(map[string]map[string]int)
	for _, c1 := range e.Candidates {
		pairwise[c1.Name] = make(map[string]int)
		for _, c2 := range e.Candidates {
			if c1.Name != c2.Name {
				pairwise[c1.Name][c2.Name] = 0
			}
		}
	}

	// Заполняем матрицу
	for _, voter := range e.Voters {
		for i, c1 := range voter.Preferences {
			for j := i + 1; j < len(voter.Preferences); j++ {
				c2 := voter.Preferences[j]
				pairwise[c1][c2]++
			}
		}
	}

	// Проверяем каждого кандидата на победу по Кондорсе
	for _, c1 := range e.Candidates {
		isCondorcetWinner := true
		for _, c2 := range e.Candidates {
			if c1.Name != c2.Name {
				if pairwise[c1.Name][c2.Name] <= pairwise[c2.Name][c1.Name] {
					isCondorcetWinner = false
					break
				}
			}
		}
		if isCondorcetWinner {
			return c1.Name
		}
	}

	return "Нет победителя по Кондорсе"
}

func main() {
	// Пример 1: Простой случай
	election1 := Election{}
	election1.AddCandidate("Петя")
	election1.AddCandidate("Вася")
	election1.AddCandidate("Оля")

	election1.AddVoter([]string{"Вася", "Оля", "Петя"})
	election1.AddVoter([]string{"Вася", "Оля", "Петя"})
	election1.AddVoter([]string{"Оля", "Вася", "Петя"})

	borda1 := election1.CalculateBordaWinner()
	condorcet1 := election1.CalculateCondorcetWinner()

	fmt.Println("Пример 1:")
	fmt.Println("Победитель по Борда:", borda1)
	fmt.Println("Победитель по Кондорсе:", condorcet1)
	if borda1 != condorcet1 {
		fmt.Println("Замечание: разные методы дали разных победителей!")
	}
	fmt.Println(strings.Repeat("-", 30))

	// Пример 2: Парадокс Кондорсе
	election2 := Election{}
	election2.AddCandidate("A")
	election2.AddCandidate("B")
	election2.AddCandidate("C")

	election2.AddVoter([]string{"A", "B", "C"})
	election2.AddVoter([]string{"B", "C", "A"})
	election2.AddVoter([]string{"C", "A", "B"})

	borda2 := election2.CalculateBordaWinner()
	condorcet2 := election2.CalculateCondorcetWinner()

	fmt.Println("Пример 2 (Парадокс Кондорсе):")
	fmt.Println("Победитель по Борда:", borda2)
	fmt.Println("Победитель по Кондорсе:", condorcet2)
	if borda2 != condorcet2 {
		fmt.Println("Замечание: разные методы дали разных победителей!")
		fmt.Println("Это демонстрирует парадокс Кондорсе, когда нет победителя по Кондорсе,")
		fmt.Println("но метод Борда дает определенного победителя.")
	}
	fmt.Println(strings.Repeat("-", 30))

	// Пример 3: Единогласное голосование
	election3 := Election{}
	election3.AddCandidate("X")
	election3.AddCandidate("Y")
	election3.AddCandidate("Z")

	for i := 0; i < 5; i++ {
		election3.AddVoter([]string{"X", "Y", "Z"})
	}

	borda3 := election3.CalculateBordaWinner()
	condorcet3 := election3.CalculateCondorcetWinner()

	fmt.Println("Пример 3 (Единогласное голосование):")
	fmt.Println("Победитель по Борда:", borda3)
	fmt.Println("Победитель по Кондорсе:", condorcet3)
	if borda3 != condorcet3 {
		fmt.Println("Замечание: разные методы дали разных победителей!")
	} else {
		fmt.Println("Оба метода согласны с победителем.")
	}
	fmt.Println(strings.Repeat("-", 30))
}
