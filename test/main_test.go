package test

import (
	"testing"
)

func Sum(i int, i2 int) int {
	return i + i2
}

func TestDummy(t *testing.T) {
	result := Sum(1, 1)
	if result != 2 {
		t.Error("What's happening ?")
	}
}
