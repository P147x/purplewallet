package models

type Categories struct {
	ID   int    `gorm:"primary_key, AUTO_INCREMENT"`
	Name string `json:"name"`
}

