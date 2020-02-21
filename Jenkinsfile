pipeline {
	 
    agent { docker { image 'golang' } }
	environment {
        XDG_CACHE_HOME  = "/tmp/.cache"
    }
    stages {
        stage('build') {
            steps {
                sh 'make build'
            }
        }
    }
}
	       
XDG_CACHE_HOME 
