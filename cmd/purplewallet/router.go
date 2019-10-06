package main

import (
	"github.com/gin-gonic/gin"
	"purplewallet/internal/controllers"
)

func InitRouter(r *gin.Engine) *gin.Engine {
	v1 := r.Group("/api/v1")


	r.POST("/api/v1/login", JWTMiddleware().LoginHandler)
	v1.Use(JWTMiddleware().MiddlewareFunc())
	controllers.Purchase(v1.Group("/purchase"))
	controllers.Wallet(v1.Group("/wallet"))
	return r
}


