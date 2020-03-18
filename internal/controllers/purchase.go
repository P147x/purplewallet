package controllers

import (
	"fmt"
	"net/http"
	"purplewallet/internal/database"
	"purplewallet/internal/models"
	"strconv"
	"time"

	"github.com/gin-gonic/gin"
)

func Purchase(r *gin.RouterGroup) {
	r.POST("", addNewPurchase)
	r.GET("/:username", getPurchaseByName)
}

func checkIfUserCanRegister(idUser int, idWallet int) bool {
	var count int
	database.GetDatabase().Table("users_wallets").Where("users_id = ? AND wallets_id = ?", idUser, idWallet).Count(&count)
	if count == 0 {
		return false
	}
	return true
}

func addNewPurchase(c *gin.Context) {
	sum, err := strconv.ParseFloat(c.PostForm("sum"), 64)
	reason := c.PostForm("reason")
	//userID, _ := strconv.ParseInt(c.DefaultPostForm("user_id", "0"), 10, 32)
	username, _ := c.Get("username")
	user, _ := getUserFromDatabase(username.(*models.Users).Username)
	wallet, _ := strconv.ParseInt(c.DefaultPostForm("wallet", "0"), 10, 32)
	owedBy, _ := strconv.ParseInt(c.DefaultPostForm("owedBy", "0"), 10, 32)
	fmt.Printf("r: " + reason + "uid: " + string(user.ID))
	if err != nil || reason == "" || user.ID == 0 || wallet == 0 {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Missing parameters"})
		return
	}
	if isUserInDatabase(int(user.ID)) == false ||
		IsWalletInDatabase(int(wallet)) == false ||
		checkIfUserCanRegister(int(user.ID), int(wallet)) == false {
		c.JSON(http.StatusBadRequest, gin.H{"error": "User is not allowed"})
		return
	}

	purchase := models.Purchase{Sum: sum, Reason: reason, Date: time.Now(), OwedBy: uint(owedBy), CategoriesID: 0, UserID: uint(user.ID), WalletID: int(wallet)}
	database.GetDatabase().Create(&purchase)
	c.String(http.StatusAccepted, "Success")
	database.Log(user.ID, "User "+string(user.ID)+" Created a new purchase on wallet "+string(wallet), 1)
}

// getPurchaseByName is used to return a list of purchases from an specific user
func getPurchaseByName(c *gin.Context) {
	username := c.Param("username")
	if username == "" {
		c.JSON(http.StatusBadRequest, gin.H{"error": "No username specified"})
	}
	// Check here if username is found in database / Return error if no user is found, otherwise, return the list

}

func getUserFromDatabase(username string) (models.Users, error) {
	var user models.Users
	if database.GetDatabase().Where("username = ?", username).First(&user).RecordNotFound() {
		return user, fmt.Errorf("No user found in records")
	}
	return user, nil
}
