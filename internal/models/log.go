package models

type Logs struct {
	ID      uint   `gorm:"primary_key, AUTO_INCREMENT"`
	Message string `json:"message"`
	UserID  uint   `json:"user_id"`
	Level   uint   `json:"level"`
}
