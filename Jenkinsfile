pipeline {
    environment {
       GOCACHE = "/tmp/.cache"
   	}
    agent { docker { image 'golang' } }
	stages {
		stage('Build') {
			steps {
				sh 'go mod download'
                sh 'go build  ./cmd/purplewallet/*.go'
			}	
		}
		stage('Test') {
			steps {
				sh 'make tests'
			}	
		}
	}
}
