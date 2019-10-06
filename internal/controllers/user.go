package controllers


import (
	"purplewallet/internal/database"
)

func isUserInDatabase(id int) bool {
	var count int
	database.GetDatabase().Table("users").Where("id = ?", id).Count(&count)
	if count == 0 {
		return false
	}
	return true
}

