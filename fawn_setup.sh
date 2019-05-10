#!/bin/bash

FAWN_HOME="${HOME}/FAWN-KV"
INSTALLATION_DIR="${HOME}"

echo "Installing required packages..."
apt install -y \
    ant \
    autoconf \
    automake \
    autotools-dev \
    bison \
    build-essential \
    cmake \
    flex \
    g++ \
    libboost-all-dev \
    libboost-dev \
    libboost-filesystem-dev \
    libboost-program-options-dev \
    libboost-test-dev \
    libboost-thread-dev \
    libevent-dev \
    libgtest-dev \
    libssl-dev \
    libtbb-dev \
    libtbb2 \
    libtool \
    m4 \
    openssl \
    patch \
    pkg-config \
    python-dev \
    ruby-dev \
    software-properties-common \
    tar \
    vim \
    wget
apt update -y
apt upgrade -y
echo "Done"

echo "Installing php..."
locale-gen en_US.UTF-8
LANG=en_US.UTF-8

add-apt-repository ppa:ondrej/php -y
apt-get update -y

apt install -y php5.6-dev
echo "Done"

echo "Installing thrift..."
tar -xjf ${FAWN_HOME}/setup/thrift-0.5.0.tar.bz2 -C ${INSTALLATION_DIR}
cd ${INSTALLATION_DIR}/thrift-0.5.0
patch -p1 < ${FAWN_HOME}/patches/fawn-thrift.patch
exit 0
./configure
make
make install
cd -
echo "Done"

echo "Installing gtest..."
tar -xzf ${FAWN_HOME}/setup/googletest-release-1.7.0.tar.gz -C ${INSTALLATION_DIR}
cd ${INSTALLATION_DIR}/googletest-release-1.7.0
cmake -DBUILD_SHARED_LIBS=ON .
make
cp -a include/gtest /usr/include/
cp -a libgtest_main.so libgtest.so /usr/lib/
cd -
echo "Done"

echo "Installing FAWN..."
cd ${FAWN_HOME}
autoreconf -is
./configure
make
cd -
echo "Done"


cd $HOME
