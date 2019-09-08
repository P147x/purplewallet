package main

import (
	"purplewallet/internal/controllers"

	"github.com/gin-gonic/gin"
)

func InitRouter(r *gin.Engine) *gin.Engine {
	v1 := r.Group("/api/v1")
	controllers.Purchase(v1.Group("/purchase"))
	controllers.Wallet(v1.Group("/wallet"))
	return r
}
