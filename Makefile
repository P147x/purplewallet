PROJECTNAME=$(shell basename "$(PWD)")

GOBASE=$(shell pwd)
GOBIN=$(GOBASE)/bin

tests:
	go test test/*.go

install:
	go mod download

build:
	go build -o $(GOBIN)/$(PROJECTNAME) ./cmd/$(PROJECTNAME)/*.go || exit

production:
	CGO_ENABLED=0 GOOS=linux GOARCH=amd64 go build -ldflags="-s -w" -o $(GOBIN)/$(PROJECTNAME) ./cmd/$(PROJECTNAME)/main.go

start:
	go build -o $(GOBIN)/$(PROJECTNAME) ./cmd/$(PROJECTNAME)/*.go || exit
	./bin/$(PROJECTNAME)
