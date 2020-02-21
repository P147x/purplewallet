pipeline {
    environment {
       GOCACHE = "/tmp/.cache"
   	}
    agent { docker { image 'golang' } }
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
