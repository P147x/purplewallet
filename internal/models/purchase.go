package models

import "time"

type Purchase struct {
	ID           uint      `gorm:"primary_key, AUTO_INCREMENT"`
	Sum          float64   `json:"sum"`
	Date         time.Time `json:"date"`
	Reason       string    `json:"reason"`
	OwedBy       int       `json:"owed_by"`
	WalletID     int       `json:"wallet_id"`
	CategoriesID int       `gorm:"foreignkey:ID"`
	UserID       int       `gorm:"foreignkey:ID"`
	Categories   Categories
	Users        Users
}
