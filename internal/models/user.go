package models

type Users struct {
	ID      int       `gorm:"primary_key, AUTO_INCREMENT"`
	Name    string    `json:”name”`
	Wallets []Wallets `gorm:"many2many:users_wallets"`
}
