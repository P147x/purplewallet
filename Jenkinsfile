pipeline {
    environment {
       GOCACHE = "/tmp/.cache"
   	}
    agent { docker { image 'golang' } }
	stages {
		stage('Build') {
			steps {
				'make build'
			}	
		}
		stage('Test') {
			steps {
				'make tests'
			}	
		}
	}
}
