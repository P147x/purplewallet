package models

type Users struct {
	ID       int       `gorm:"primary_key, AUTO_INCREMENT"`
	Name     string    `json:”name”`
	Username string    `json:”username”`
	Password string    `json:"password`
	Wallets  []Wallets `gorm:"many2many:users_wallets"`
}
