package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
	"github.com/jinzhu/configor"
	"github.com/jinzhu/gorm"

	"log"
	"strconv"

	_ "github.com/jinzhu/gorm/dialects/mysql"

	models "purplewallet/internal/models"
)

func addUser(c *gin.Context) {
	name := c.PostForm("name")
	c.String(http.StatusOK, "Hello %s", name)
}

func Init_router(r *gin.Engine) *gin.Engine {
	r.POST("/user", addUser)
	return r
}

func main() {
	var db gorm.DB
	r := gin.Default()
	r = Init_router(r)
	configor.Load(&Config, "config/config.yaml")
	if init_database(&db) == false {
		return
	}
	r.Run(":" + strconv.Itoa(Config.Port))
	defer db.Close()
}

func init_database(db *gorm.DB) bool {
	c_string := Config.Database.User + ":" + Config.Database.Password + "@tcp(" + Config.Database.URL + ":" + strconv.Itoa(Config.Database.Port) + ")/" + Config.Database.DBName + "?charset=utf8&parseTime=True"
	db, err := gorm.Open("mysql", c_string)
	log.Println("Connection to database started")

	if err != nil {
		log.Fatalln("Error occured: " + err.Error())
		return false
	}
	log.Println("Success")
	db.LogMode(true)
	db.AutoMigrate(&models.Categories{})
	db.AutoMigrate(&models.Users{})
	db.AutoMigrate(&models.Wallets{})
	db.AutoMigrate(&models.Transactions{})

	return true
}
