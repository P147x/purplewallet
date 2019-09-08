package controllers

import (
	"log"
	"net/http"
	"purplewallet/internal/database"
	"purplewallet/internal/models"
	"purplewallet/internal/serializable"
	"strconv"

	"github.com/gin-gonic/gin"
)

func Wallet(r *gin.RouterGroup) {
	r.GET("/balance/:wallet", getBalance)
	//r.GET("/balance/:wallet/:user", getBalance)
}

func getBalance(c *gin.Context) {
	wallet, _ := strconv.ParseInt(c.Param("wallet"), 10, 64)
	if wallet == 0 || IsWalletInDatabase(int(wallet)) == false {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Missing parameters"})
		return
	}
	wlt := serializable.WalletBalance{}
	wlt.NbUsers = getNumberOfUsersInWallet(int(wallet))
	if wlt.NbUsers == 0 {
		c.JSON(http.StatusBadRequest, gin.H{"error": "No user found in wallet"})
		return
	}
	wlt.Users = make([]serializable.UserBalance, wlt.NbUsers)
	wlt.WalletID = int(wallet)
	users := getUsersInWallet(int(wallet))
	for i, user := range users {
		wlt.Users[i].UserID = user.ID
	}
	var purchases []models.Purchase
	purchases = getWalletPurchases(wlt.WalletID)
	for i, user := range wlt.Users {
		for _, purchase := range purchases {
			if purchase.UserID == user.UserID {
				wlt.Users[i].Total += purchase.Sum
				if purchase.OwedBy == 0 {
					wlt.Users[i].CommonPurchases += purchase.Sum
				}
			} else if user.UserID == purchase.OwedBy {
				wlt.Users[i].Debts += purchase.Sum
			}
		}
		wlt.Users[i].Balance = (wlt.Users[i].CommonPurchases / float64(wlt.NbUsers)) - wlt.Users[i].Debts
	}
	totalCommonsFees := getWalletTotalCommonsFees(wlt.Users)
	for i := range users {
		wlt.Users[i].Balance = wlt.Users[i].Total - (totalCommonsFees / float64(wlt.NbUsers)) - wlt.Users[i].Debts
	}

	c.JSON(http.StatusAccepted, wlt)
}

func getWalletTotalCommonsFees(users []serializable.UserBalance) float64 {
	var total float64
	total = 0
	for _, user := range users {
		total += user.CommonPurchases
	}
	return total
}

//func getUserDebts(wallet int, user int) models.Purchase {}
func getWalletPurchases(walletID int) []models.Purchase {
	var purchases []models.Purchase
	database.GetDatabase().Where("wallet_id = ?", walletID).Find(&purchases)
	log.Println(purchases)
	return purchases
}

func getNumberOfUsersInWallet(wallet int) int {
	var count int
	database.GetDatabase().Table("users_wallets").Where("wallets_id = ?", wallet).Count(&count)
	return count
}

func getUsersInWallet(wallet int) []models.Users {
	var users []models.Users
	wlt := models.Wallets{}
	database.GetDatabase().First(&wlt, "id = ?", wallet)
	database.GetDatabase().Model(&wlt).Related(&users, "Users")
	return users
}

func IsWalletInDatabase(id int) bool {
	var count int
	database.GetDatabase().Table("wallets").Where("id = ?", id).Count(&count)
	if count == 0 {
		return false
	}
	return true
}
