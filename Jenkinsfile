pipeline {
	 
    agent { docker { image 'golang' } }
	environment {
        XDG_CACHE_HOME  = "/tmp/.cache"
    }
    stages {
        stage('build') {
            steps {
		sh 'go mod download'
                sh 'go build  ./cmd/purplewallet/*.go'
            }
        }
    }
}
	       
XDG_CACHE_HOME 
