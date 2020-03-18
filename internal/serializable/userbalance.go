package serializable

// UserBalance is used to contain a resume of the user dispences
type UserBalance struct {
	UserID          uint
	CommonPurchases float64
	Debts           float64
	Total           float64
	Balance         float64
}
