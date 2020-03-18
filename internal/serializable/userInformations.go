package serializable

import "purplewallet/internal/models"

type UserInformation struct {
	Threshold uint
	Role      int
	Wallets   []models.Wallets
}
