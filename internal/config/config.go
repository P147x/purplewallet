package config

var Config = struct {
	Port     int `default:"8080"`
	Database struct {
		Password string `required:"true" env:"DBPassword"`
		User     string
		URL      string
		DBName   string
		Port     int `default:"3306"`
	}
}{}
