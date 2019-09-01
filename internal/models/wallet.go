package models

type Wallets struct {
	ID           int        `gorm:"primary_key, AUTO_INCREMENT"`
	Name         string     `json:"name"`
	Users        []Users    `gorm:"many2many:users_wallets"`
	Transactions []Purchase `gorm:"ForeignKey:ID"`
}
