pipeline {
	 
    agent { docker { image 'golang' } }
    stages {
        stage('build') {
            steps {
		sh 'export GOCACHE = "/tmp/.cache"'
		sh 'go mod download'
                sh 'go build  ./cmd/purplewallet/*.go'
            }
        }
    }
}
	       
XDG_CACHE_HOME 
