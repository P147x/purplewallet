pipeline {
    environment {
       GOCACHE = "/tmp/.cache"
   	}
    agent { docker { image 'golang' } }
    stages('Build' {
		steps {
			'make build'
		}	
	}
	stages('test' {
		steps {
			'make tests'
		}	
	}
}
