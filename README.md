# PurpleWallet 

Purplewallet is an easy wallet manager, for watching your spendings or manage your money with your friends.. or both !

[![Go Report Card](https://goreportcard.com/badge/github.com/P147x/purplewallet)](https://goreportcard.com/report/github.com/P147x/purplewallet)




## Getting started
### Prerequisites

You need to write a correct configuration file in order to get that program working. Your configuration file should be placed in `./config/config.yaml`. Here is an exemple of a basic configuration file :
```
port: 8080

database:
  url: "exemple.com"
  user: "user"
  password: "pass_word"
  port: 3306
  dbname: "purplewallet"
```

Once your access to the database are in place from the configuration file, you have to create the database with the name you gave in the configuration file. The tables are going to be created automatically at your first start.

### Installation


Generate a binary using the Makefile, and move the binary to the root of the repository to let the binary access to the configuration file :
```
make build
cp bin/purplewallet .
```
You can also run directly run using the Makefile !

```
make start
```

Once your program is running, you have to insert some mandatory data manually (like users and wallets).


## Basic routes

### Purchases (*/api/v1/purchase*)
Purchases routes are built to add, remove or update transactions you have made and you want to register in your wallet.
#### *`/purchase`*
Gives you some informations about user spendings from a wallet and compares who owes money to whom.
* **Method:**

	`POST`
  
*  **URL Params**
  
   **Required:**
 
   `wallet=1`
   
   `user_id=1`
   
   `sum=12.3`

	**Optionnal:**
    
    `owedBy=2`

### Wallet (*/api/v1/wallet*)
Wallet routes are here to create/delete a wallet or get informations from a wallet.
#### *`/balance/:wallet`*
Gives you some informations about user spendings from a wallet and compares who owes money to whom.
* **Method:**

	`GET`
  
*  **URL Params**
   **Required:**
 
   `wallet=1`



## Authors

* **Lucas DEBOUTÉ** - *What have i done*
* **Victor HOARAU** - *It's a me* 
## Built with
- [gin](https://github.com/gin-gonic/gin) - Lightweight HTTP web framework used for requests
- [gorm](https://github.com/jinzhu/gorm) - ORM for Go
- [configor](https://github.com/jinzhu/configor) - Configuration tool

## Versioning
We use the [Sermver](https://semver.org/) for versionning this project.
