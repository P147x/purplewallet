package models

type Transactions struct {
	ID           int    `gorm:"primary_key, AUTO_INCREMENT"`
	Date         string `json:"date"`
	Reason       string `json:"reason"`
	CategoriesID int    `gorm:"foreignkey:ID"`
	Categories   Categories
}
