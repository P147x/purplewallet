package main

import "github.com/jinzhu/configor"
import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)
import "log"
import "strconv"

type Wallets struct {
	ID           int            `gorm:"primary_key, AUTO_INCREMENT"`
	Name         string         `json:"name"`
	Users        []Users        `gorm:"many2many:users_wallets"`
	Transactions []Transactions `gorm:"ForeignKey:ID"`
}

type Users struct {
	ID      int       `gorm:"primary_key, AUTO_INCREMENT"`
	Name    string    `json:”name”`
	Wallets []Wallets `gorm:"many2many:users_wallets"`
}

type Categories struct {
	ID   int    `gorm:"primary_key, AUTO_INCREMENT"`
	Name string `json:"name"`
}

type Transactions struct {
	ID           int    `gorm:"primary_key, AUTO_INCREMENT"`
	Date         string `json:"date"`
	Reason       string `json:"reason"`
	CategoriesID int    `gorm:"foreignkey:ID"`
	Categories   Categories
}

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
	tr := Transactions{}

	//restitution
	var users []Users
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
	db.AutoMigrate(&Categories{})
	db.AutoMigrate(&Users{})
	db.AutoMigrate(&Wallets{})
	db.AutoMigrate(&Transactions{})
	test_dummies_entries(db)
	defer db.Close()
	return true
}
