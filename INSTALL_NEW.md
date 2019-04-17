# Installation guide

<ul>
<li>Clone FAWN
<li>Install php5
<ul>
<li>https://vitux.com/how-to-install-php5-and-php7-on-ubuntu-18-04-lts/
<li>https://askubuntu.com/questions/393638/unicodedecodeerror-ascii-codec-cant-decode-byte-0x-in-position-ordinal-n
<li>`sudo apt install php5.6-dev`
</ul>
<li>Install thrift 0.5.0 
<ul>
<li>https://archive.apache.org/dist/incubator/thrift/0.5.0-incubating/
<li>https://thrift-tutorial.readthedocs.io/en/latest/installation.html
<li>setup.rb:788:in `load_rbconfig': uninitialized constant Config (NameError)
<ul>
<li>https://github.com/piersharding/ruby-sapnwrfc/pull/5/commits/c1bc8ab9a446a3c452e1a324380b4d9272a825ac
</ul>
<li>error: ‘function_entry’ does not name a type
<ul>
<li>https://issues.apache.org/jira/browse/THRIFT-1577
</ul>
</ul>
<li>Install gtest
<ul>
<li>https://github.com/google/googletest/archive/release-1.7.0.tar.gz
<li>`cmake -DBUILD_SHARED_LIBS=ON .`
<li>`make`
<li>`sudo cp -a include/gtest /usr/include/`
<li>`sudo cp -a libgtest_main.so libgtest.so /usr/lib/`
</ul>
<li>Install boost
<ul>
<li>sudo apt-get install libboost-all-dev
</ul>
<li>Install openssl >= 1.1.0
<ul>
<li>https://stackoverflow.com/a/46769674
</ul>
</ul>
