package main

import (
	"fmt"
	"math/rand"
	"time"
)

// Тип для функции стратегии
type Strategy func(int, []bool, []bool) bool

// Стратегии
func alwaysCooperate(round int, self, enemy []bool) bool {
	return true
}

func alwaysBetray(round int, self, enemy []bool) bool {
	return false
}

func titForTat(round int, self, enemy []bool) bool {
	if round == 0 {
		return true
	}
	return enemy[len(enemy)-1]
}

// Функция игры
func playGame(strategy1, strategy2 Strategy, rounds int) (int, int) {
	var choices1, choices2 []bool
	score1, score2 := 0, 0

	for round := 0; round < rounds; round++ {
		choice1 := strategy1(round, choices1, choices2)
		choice2 := strategy2(round, choices2, choices1)

		choices1 = append(choices1, choice1)
		choices2 = append(choices2, choice2)

		switch {
		case choice1 && choice2: // Оба сотрудничают
			score1 += 24
			score2 += 24
		case !choice1 && !choice2: // Оба предают
			score1 += 4
			score2 += 4
		case choice1 && !choice2: // 1 сотрудничает, 2 предает
			score2 += 20
		default: // 1 предает, 2 сотрудничает
			score1 += 20
		}
	}

	return score1, score2
}

func main() {
	rand.Seed(time.Now().UnixNano())
	rounds := 100 + rand.Intn(101) // 100-200 раундов

	fmt.Printf("Количество раундов: %d\n\n", rounds)

	// Тестируем разные стратегии
	strategies := []struct {
		name string
		fn   Strategy
	}{
		{"Всегда сотрудничать", alwaysCooperate},
		{"Всегда предавать", alwaysBetray},
		{"Око за око", titForTat},
	}

	for i := 0; i < len(strategies); i++ {
		for j := i + 1; j < len(strategies); j++ {
			s1, s2 := strategies[i], strategies[j]
			score1, score2 := playGame(s1.fn, s2.fn, rounds)
			
			fmt.Printf("%s vs %s:\n", s1.name, s2.name)
			fmt.Printf("  %s: %d очков\n", s1.name, score1)
			fmt.Printf("  %s: %d очков\n", s2.name, score2)
			
			if score1 > score2 {
				fmt.Printf("  Победил: %s\n\n", s1.name)
			} else if score2 > score1 {
				fmt.Printf("  Победил: %s\n\n", s2.name)
			} else {
				fmt.Println("  Ничья!\n")
			}
		}
	}
}
