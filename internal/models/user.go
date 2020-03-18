package models

type Users struct {
	ID              uint      `gorm:"primary_key, AUTO_INCREMENT"`
	Name            string    `json:”name”`
	Username        string    `json:”username”`
	Password        string    `json:"password`
	MonthlyExpenses uint      `json:"monthly_expenses`
	Role            int       `json:"role`
	Wallets         []Wallets `gorm:"many2many:users_wallets"`
}
