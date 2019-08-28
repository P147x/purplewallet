package main

import "github.com/jinzhu/configor"
import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)
import "log"
import "strconv"

var Config = struct {
	Database struct {
		Password string `required:"true" env:"DBPassword"`
		User     string
		Url      string
		DBName   string
		Port     uint `default:"3306"`
	}
}{}

func main() {
	configor.Load(&Config, "config/config.yaml")
	init_database()
}

func init_database() {
	c_string := Config.Database.User + ":" + Config.Database.Password + "@tcp(" + Config.Database.Url + ":" + strconv.Itoa(Config.Database.Port) + ")/" + Config.Database.DBName + "?charset=utf8&parseTime=True"
	log.Println("Connection to database started")
	db, err := gorm.Open("mysql", c_string)
	if err != nil {
		log.Fatalln("Error occured: " + err.Error())
	}
	log.Println("Success")
	db.LogMode(true)
	defer db.Close()
}
