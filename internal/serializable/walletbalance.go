package serializable

type WalletBalance struct {
	WalletID int
	NbUsers  int
	Users    []UserBalance
}
