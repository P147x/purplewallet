package main

import (
	"encoding/hex"
	jwt "github.com/appleboy/gin-jwt/v2"
	"github.com/gin-gonic/gin"
	"purplewallet/internal/config"
	"purplewallet/internal/database"
	"purplewallet/internal/models"
	"time"

	"crypto/md5"
	"fmt"
)


type login struct {
	Username string `form:"username" json:"username" binding:"required"`
	Password string `form:"password" json:"password" binding:"required"`
}

func MD5(text string) string {
	algorithm := md5.New()
	algorithm.Write([]byte(text))
	return hex.EncodeToString(algorithm.Sum(nil))
}

func GetUserFromDatabase(name string, password string) (models.Users, error) {
	var user models.Users
	if database.GetDatabase().Where("username = ? AND password = ?", name, MD5(password)).First(&user).RecordNotFound() {
		return user, fmt.Errorf("No user found in records")
	}

	return user, nil
}

var identityKey = "username"

func JWTMiddleware() *jwt.GinJWTMiddleware {
	authMiddleware, _ := jwt.New(&jwt.GinJWTMiddleware{
		Realm:       "test zone",
		Key:         []byte(config.Config.JWT),
		Timeout:     time.Hour,
		MaxRefresh:  time.Hour,
		IdentityKey: identityKey,
		Authenticator: func(c *gin.Context) (interface{}, error) {
			var loginVals login
			if err := c.ShouldBind(&loginVals); err != nil {
				return "", jwt.ErrMissingLoginValues
			}

			user, err := GetUserFromDatabase(loginVals.Username, loginVals.Password)

			if err == nil {
				return user, nil
			}

			return nil, jwt.ErrFailedAuthentication
		},
		PayloadFunc: func(data interface{}) jwt.MapClaims {
			if v, ok := data.(models.Users); ok {
				return jwt.MapClaims{
					identityKey: v.Username,
				}
			}
			return jwt.MapClaims{}
		},
		IdentityHandler: func(c *gin.Context) interface{} {
			claims := jwt.ExtractClaims(c)
			return &models.Users{
				Username: claims[identityKey].(string),
			}
		},

		Authorizator: func(data interface{}, c *gin.Context) bool {
			fmt.Print(data)
			if _, ok := data.(*models.Users); ok {
				return true
			}
			return false
		},
		Unauthorized: func(c *gin.Context, code int, message string) {
			c.JSON(code, gin.H{
				"code":    code,
				"message": message,
			})
		},
		TokenLookup: "header: Authorization, query: token, cookie: jwt",
		TokenHeadName: "Bearer",
		TimeFunc: time.Now,
	})
	return authMiddleware
}