pipeline {
    environment {
       GOCACHE = "/tmp/.cache"
   	}
    agent { docker { image 'golang' } }
	stages {
		tage('Build' {
			steps {
				'make build'
			}	
		}
		stage('test' {
			steps {
				'make tests'
			}	
		}
	}
}
