package controllers

import (
	"net/http"
	"purplewallet/internal/database"
	"purplewallet/internal/models"
	"purplewallet/internal/serializable"

	"github.com/gin-gonic/gin"
)

func User(r *gin.RouterGroup) {
	r.PUT("/:id", getBalance)
	r.GET("/account", getUser)
}

// updateAccount is used to change user password or expenses
func updateAccount(c *gin.Context) {

	//user, _ := c.Get("username")
	//pass := c.PostForm("pass")
	//username, _ := c.Get("username")

}

// Retuns necessary informations after login
func getUser(c *gin.Context) {
	u, _ := c.Get("username")
	r := serializable.UserInformation{}

	r.Threshold = u.(*models.Users).MonthlyExpenses
	r.Role = u.(*models.Users).Role
	user, _ := getUserFromDatabase(u.(*models.Users).Username)

	database.GetDatabase().Model(&user).Related(&r.Wallets, "Wallets")
	c.JSON(http.StatusAccepted, r)
}

func getUserInformationInDatabase(n string) models.Users {
	user := models.Users{}
	database.GetDatabase().Table("users").Where("username = ?", n).First(&user)
	return user
}

func isUserInDatabase(id int) bool {
	var count int
	database.GetDatabase().Table("users").Where("id = ?", id).Count(&count)
	if count == 0 {
		return false
	}
	return true
}
