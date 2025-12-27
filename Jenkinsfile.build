pipeline {
  agent any

  options {
    timestamps()
  }

  stages {
    stage('Checkout') {
      steps { checkout scm }
    }

    stage('Toolchain sanity') {
      steps {
        sh '''
          set -eux
          cmake --version
          arm-none-eabi-gcc --version
          make --version
        '''
      }
    }

    stage('Configure') {
      steps {
        sh '''
          set -eux
          cmake -G "Unix Makefiles" -S . -B build \
            -DCMAKE_BUILD_TYPE=Debug \
            -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi-gcc.cmake \
            -DCMAKE_EXPORT_COMPILE_COMMANDS=1
        '''
      }
    }

    stage('Build') {
      steps {
        sh '''
          set -eux
          cmake --build build
        '''
      }
    }

    stage('Archive artifacts') {
      steps {
        archiveArtifacts artifacts: 'build/**/*.{elf,hex,bin,map}', allowEmptyArchive: true
      }
    }
  }
}
