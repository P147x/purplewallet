package controllers

import (
	"log"
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

func addNewPurchase(c *gin.Context) {
	sum, err := strconv.ParseFloat(c.PostForm("sum"), 64)
	reason := c.PostForm("reason")
	userID := c.PostForm("user_id")
	log.Printf("%f, %s, %s", sum, reason, userID)
	if err != nil || reason == "" || userID == "" {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Missing parameters"})
		return
	}
	purchase := models.Purchase{Sum: sum, Reason: reason, Date: time.Now(), OwedBy: 0, CategoriesID: 0, UserID: 0}
	database.GetDatabase().Create(&purchase)
	c.String(http.StatusAccepted, "oui")
}

// getPurchaseByName is used to return a list of purchases from an specific user
func getPurchaseByName(c *gin.Context) {
	username := c.Param("username")
	if username == "" {
		c.JSON(http.StatusBadRequest, gin.H{"error": "No username specified"})
	}
	// Check here if username is found in database / Return error if no user is found, otherwise, return the list

}
