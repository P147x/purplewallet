package database

import (
	"log"
	"purplewallet/internal/config"
	"purplewallet/internal/models"
	"strconv"

	"github.com/jinzhu/gorm"
)

var db *gorm.DB

//GetDatabase is a singleton for getting the instance of the database
func GetDatabase() *gorm.DB {
	if db == nil {
		InitDatabase()
	}
	return db
}

// InitDatabase is used for the first instanciation of the database, connecting to the server and creating the missing tables.
func InitDatabase() {
	cstr := config.Config.Database.User + ":" + config.Config.Database.Password + "@tcp(" + config.Config.Database.URL + ":" + strconv.Itoa(config.Config.Database.Port) + ")/" + config.Config.Database.DBName + "?charset=utf8&parseTime=True"
	var err error
	db, err = gorm.Open("mysql", cstr)
	log.Println("Connection to database started")

	if err != nil {
		log.Fatalln("Error occured: " + err.Error())
		return
	}
	log.Println("Success")
	db.LogMode(true)
	db.AutoMigrate(&models.Categories{})
	db.AutoMigrate(&models.Users{})
	db.AutoMigrate(&models.Wallets{})
	db.AutoMigrate(&models.Purchase{})
	//defer db.Close()
	return
}
