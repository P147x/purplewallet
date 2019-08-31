package main

import "github.com/jinzhu/configor"
import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)
import "log"
import "strconv"
import models "purplewallet/internal/models"

var Config = struct {
	Database struct {
		Password string `required:"true" env:"DBPassword"`
		User     string
		Url      string
		DBName   string
		Port     int `default:"3306"`
	}
}{}

func main() {
	configor.Load(&Config, "config/config.yaml")
	if init_database() == false {
		return
	}

}

func test_dummies_entries(db *gorm.DB) {
	/*user := Users{Name: "Lucas"}
	db.Create(&user)
	user = Users{Name: "Victor"}
	db.Create(&user)*/
	//cat := Categories{Name: "Courses"}
	//db.Create(&cat)
	//tr := models.Transactions{}

	//restitution
	var users []models.Users
	db.Find(&users)
	for _, us := range users {
		log.Println(us.Name)
	}
	log.Println(users[0])

}

func init_database() bool {
	c_string := Config.Database.User + ":" + Config.Database.Password + "@tcp(" + Config.Database.Url + ":" + strconv.Itoa(Config.Database.Port) + ")/" + Config.Database.DBName + "?charset=utf8&parseTime=True"
	log.Println("Connection to database started")
	db, err := gorm.Open("mysql", c_string)
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
	test_dummies_entries(db)
	defer db.Close()
	return true
}
