package main

import (
	"purplewallet/internal/config"
	"purplewallet/internal/database"

	"github.com/gin-gonic/gin"
	"github.com/jinzhu/configor"

	"strconv"

	_ "github.com/jinzhu/gorm/dialects/mysql"
)

func main() {
	r := gin.Default()

	configor.Load(&config.Config, "config/config.yaml")

	r = InitRouter(r)
	r.Run(":" + strconv.Itoa(config.Config.Port))
	database.CloseDatabase()
}
