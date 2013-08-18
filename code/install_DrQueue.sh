#!/bin/bash

CHECKHOSTNAME=$(hostname | awk -F. '{print $3}')

if [ $CHECKHOSTNAME == "" ]; then
    echo 'Hostname not FQDN!'
    exit 1
fi

SOURCE_DIR="/opt"
INSTALL_DIR="/etc"
LDAP_DC=$(hostname | awk -F. '{print $2"."$3}')
IPADDR=$(ifconfig eth0 | grep 'inet addr' | awk '{print $2}' | awk -F: '{print $2}')
DB_NAME="DrQueueOnRails"
USER_NAME="drqueue"
PASSWORD="drqueue"
# IPTABLES OFF
iptables -F
iptables -t nat -F
/etc/init.d/iptables save
/etc/init.d/iptables stop
chkconfig iptables off

# SELINUX OFF
setenforce 0
sed -i 's/SELINUX=.*$/SELINUX=disabled/g' /etc/selinux/config

# YUM REPO
rpm -viUh http://apt.sw.be/redhat/el6/en/x86_64/rpmforge/RPMS/rpmforge-release-0.5.2-2.el6.rf.x86_64.rpm
rpm -viUh http://dl.fedoraproject.org/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm

# RPM REQUIRE
yum -y install scons bzip2 unzip zip nmap openssl lynx ncftp gcc gcc-c++ httpd httpd-devel mysql-server pkgconfig php php-gd php-ldap php-xml php-xmlrpc curl curl-devel perl-libwww-perl libxml2 libxml2-devel mod_python ntp gtk2-devel gtk2 python-devel swig scons tcsh pygtk2-devel pkgconfig vnc-server fuse fuse-ntfs-3g gnome-session ImageMagick mod_xsendfile blender
yum -y install libyaml-devel ruby ruby-devel ruby-libs ruby-irb ruby-rdoc ruby-mysql rubygems
rpm -vhiU http://download.longgeek.com/Puppet_for_rhel6.2/ruby-devel-1.8.7.352-3.el6.x86_64.rpm
rpm -vhiU http://download.longgeek.com/Puppet_for_rhel6.2/ruby-rdoc-1.8.7.352-3.el6.x86_64.rpm
rpm -vhiU http://download.longgeek.com/Puppet_for_rhel6.2/rubygems-1.3.7-1.el6.noarch.rpm

# DrQueue
wget http://www.drqueue.org/files/drqueue.0.64.4c3.tgz -P $SOURCE_DIR
cd $SOURCE_DIR
tar zxvf drqueue.0.64.4c3.tgz
cd DrQueue-0.64.4c3
scons
scons install PREFIX=$INSTALL_DIR
cd python
python setup.py install
sleep 5
python setup.py install

cat > $INSTALL_DIR/drqueue/etc/master.conf << _GEEK_
logs=$INSTALL_DIR/drqueue/logs
tmp=$INSTALL_DIR/drqueue/tmp
db=$INSTALL_DIR/drqueue/db
bin=$INSTALL_DIR/drqueue/bin
etc=$INSTALL_DIR/drqueue/etc
_GEEK_

cat > $INSTALL_DIR/drqueue/etc/slave.conf << _GEEK_
logs=$INSTALL_DIR/drqueue/logs
tmp=$INSTALL_DIR/drqueue/tmp
pool=test1,test2,test3
_GEEK_

cat > $INSTALL_DIR/drqueue/etc/drqman.conf << _GEEK_
logs=$INSTALL_DIR/drqueue/logs
tmp=$INSTALL_DIR/drqueue/tmp
db=$INSTALL_DIR/drqueue/db
_GEEK_

cat >> /etc/profile << _GEEK_
PATH=${PATH}:$INSTALL_DIR/drqueue/bin
export PATH
export DRQUEUE_ROOT=$INSTALL_DIR/drqueue
export DRQUEUE_TMP=$INSTALL_DIR/drqueue/tmp
export DRQUEUE_OS=LINUX
export DRQUEUE_BIN=$INSTALL_DIR/drqueue/bin
export DRQUEUE_ETC=$INSTALL_DIR/drqueue/etc
export DRQUEUE_DB=$INSTALL_DIR/drqueue/db
export DRQUEUE_LOGS=$INSTALL_DIR/drqueue/logs
export OLDPWD='$SOURCE_DIR/DrQueue-0.64.4c3/DrQueueOnRails/config'
export DRQUEUE_MASTER=$IPADDR
export RAILS_ENV=production
_GEEK_
source /etc/profile

# RUBY GEM
gem sources -a http://ruby.taobao.org
gem install rake -v 0.8.7 -V
gem install rails -v 2.3.5 -V
yum -y install bzip2-devel libXt-devel libjpeg-devel libtiff-devel
rpm -Uvhi ftp://ftp.pbone.net/mirror/ftp.scientificlinux.org/linux/scientific/6.2/x86_64/os/Packages/ghostscript-devel-8.70-11.el6_1.2.x86_64.rpm
rpm -Uvhi http://mirror.centos.org/centos/6/os/x86_64/Packages/lcms-devel-1.19-1.el6.x86_64.rpm
rpm -Uvhi ftp://ftp.procmail.org/pub/linux/centos/6.0/os/x86_64/Packages/jasper-devel-1.900.1-15.el6.x86_64.rpm
rpm -Uvhi ftp://ftp.mirrorservice.org/sites/ftp.scientificlinux.org/linux/scientific/6.0/x86_64/os/Packages/ImageMagick-devel-6.5.4.7-5.el6.x86_64.rpm
gem install rmagick -V
yum -y install swig git
gem install DrQueueRubyBindings -V
gem install ruby-net-ldap
gem sources -a http://gems.github.com
gem install mislav-will_paginate -V
gem install mongrel -V

# DrQueueOnRails
cd $SOURCE_DIR/DrQueue-0.64.4c3/DrQueueOnRails/config
cat > database.yml << _GEEK_
production:
  adapter: mysql
  database: $DB_NAME
  username: $USER_NAME
  password: $PASSWORD
  host: $IPADDR
_GEEK_

cat > environment.rb << _GEEK_
ENV['DRQUEUE_MASTER'] ||= '$IPADDR'
ENV['DRQUEUE_TMP'] ||= '$INSTALL_DIR/drqueue/tmp'
ENV['DRQUEUE_ETC'] ||= '$INSTALL_DIR/drqueue/etc'
ENV['DRQUEUE_LOGS'] ||= '$INSTALL_DIR/drqueue/logs'
ENV['LDAP_TREEBASE'] ||= "dc=$LDAP_DC"
ENV['LDAP_HOST'] ||= "$IPADDR"
ENV['LDAP_PORT'] ||= "389"
ENV['LDAP_FILTER'] ||= "uid"
ENV['LDAP_ATTRS'] ||= "cn"
ENV['WEB_PROTO'] ||= "http"
ENV['USER_STATUS'] ||= "demo,student,advanced,admin"
ENV['USER_QUOTA'] ||= "0.5,5,15,35"
ENV['USER_PRIO'] ||= "100,500,750,1000"
ENV['USER_ADMIN_PW'] ||= "password"
ENV['LOG_SHOW_USER'] ||= "account name"
ENV['LOG_SHOW_PW'] ||= "password"
ENV['DQOR_USER'] ||= "drqueueonrails"
ENV['DQOR_GROUP'] ||= "drqueueonrails"
# ENV['AVAIL_RENDERERS'] ||= "blender,blenderlux,cinema4d,luxrender,maya,mayamr,mentalray,vray"
ENV['AVAIL_RENDERERS'] ||= "mentalray"
ENV['DQOR_TUTORIALS'] ||= "true"
ENV['DQOR_SHOW_FRAME_IMG'] ||= "true"
ENV['DQOR_SLAVES_CACHE_TIME'] ||= "600"
# APP_VERSION = IO.popen("git show --abbrev-commit | head -n 1").readline.split(" ")[1]
APP_VERSION = ""
RAILS_GEM_VERSION = '2.3.5' unless defined? RAILS_GEM_VERSION
require File.join(File.dirname(__FILE__), 'boot')
Rails::Initializer.run do |config|
  config.action_controller.session = { :session_key => "_dqor_session", :secret => "gfcgfkhjt56gfcdesxdtrr54w3fdxfhgffge55454565" } 
end
require 'will_paginate'
_GEEK_

/etc/init.d/mysqld start
chkconfig mysqld on
mysqladmin -uroot password password
mysql -uroot -ppassword -e "create database $DB_NAME;"
mysql -uroot -ppassword -e "grant all on $DB_NAME.* to '$USER_NAME'@'$IPADDR' identified by '$PASSWORD';"
mysql -uroot -ppassword -e "grant all on $DB_NAME.* to '$USER_NAME'@'%' identified by '$PASSWORD';"
mysql -uroot -ppassword -e "grant all on $DB_NAME.* to '$USER_NAME'@'localhost' identified by '$PASSWORD';"
rake RAILS_ENV=production db:migrate
mysql -uroot -ppassword -e "insert into $DB_NAME.profiles(name,email,avatar,ldap_account,status,accepted) values('Admin Account','admin@$LDAP_DC','NULL','admin','admin','1');"
mysql -uroot -ppassword -e "insert into $DB_NAME.profiles(name,email,avatar,ldap_account,status,accepted) values('Demo Account','demo@$LDAP_DC','NULL','demo','demo','0');"

## LDAP
yum -y install openldap-servers openldap-clients migrationtools
echo "BASE dc=$LDAP_DC\tURI ldap://$IPADDR" >> /etc/openldap/ldap.conf
cp /usr/share/openldap-servers/slapd.conf.obsolete /etc/openldap/slapd.conf
cp /usr/share/openldap-servers/DB_CONFIG.example /var/lib/ldap/DB_CONFIG
chown -R ldap:ldap /var/lib/ldap
sed -i "/suffix.*$/ s/\"dc=my-domain,dc=com\"/\"dc=$LDAP_DC\"/g" /etc/openldap/slapd.conf
sed -i "/rootdn.*$/ s/\"cn=Manager,dc=my-domain,dc=com\"/\"cn=$(hostname | awk -F. '{print $1}'),dc=$LDAP_DC\"\nrootpw\t\tpassword/g" /etc/openldap/slapd.conf
sed -i "s/padl.com/$LDAP_DC/g" /usr/share/migrationtools/migrate_common.ph
sed -i "s/dc=padl,dc=com/dc=$LDAP_DC/g" /usr/share/migrationtools/migrate_common.ph

cat > /usr/share/migrationtools/base.ldif << _GEEK_
dn: dc=$LDAP_DC
dc: $LDAP_DC
objectClass: top
objectClass: domain

dn: ou=People,dc=$LDAP_DC
ou: People
objectClass: top
objectClass: organizationalUnit

dn: ou=Group,dc=$LDAP_DC
ou: Group
objectClass: top
objectClass: organizationalUnit
_GEEK_

/etc/init.d/slapd start
rm -fr /etc/openldap/slapd.d/*
slaptest -f /etc/openldap/slapd.conf -F /etc/openldap/slapd.d
chown -R ldap:ldap /etc/openldap/slapd.d/
/etc/init.d/slapd restart
chkconfig slapd on
ldapadd  -D "cn=$(hostname | awk -F. '{print $1}'),dc=$LDAP_DC" -w password -x  -f /usr/share/migrationtools/base.ldif

rm -fr /opt/.DrQueueOnRails-CN
git clone https://github.com/longgeek/DrQueueOnRails-CN.git /opt/.DrQueueOnRails-CN
cp -r /opt/.DrQueueOnRails-CN/app/views $SOURCE_DIR/DrQueue-0.64.4c3/DrQueueOnRails/app/
cp -r /opt/.DrQueueOnRails-CN/app/controllers $SOURCE_DIR/DrQueue-0.64.4c3/DrQueueOnRails/app/
cp /opt/.DrQueueOnRails-CN/code/* /opt
cp /opt/.DrQueueOnRails-CN/code/create_user.sh /usr/sbin/create-user
chmod +x /usr/sbin/create-user

cat > /etc/yum.repos.d/longgeek.repo << _GEEK_
[longgeek]
name=longgeek repo
baseurl=http://download.longgeek.com/Puppet_for_rhel6.2/
gpgcheck=0
_GEEK_
yum install -y ruby ruby-libs ruby-devel httpd httpd-devel rubygem-passenger mod_passenger

cat > /etc/httpd/conf.d/passenger.conf << _GEEK_
LoadModule passenger_module modules/mod_passenger.so
<IfModule mod_passenger.c>
   RailsEnv production

   PassengerRoot /usr/share/rubygems/gems/passenger-3.0.21
   PassengerRuby /usr/bin/ruby

   PassengerHighPerformance on
   PassengerMaxPoolSize 12
   PassengerPoolIdleTime 1500
   PassengerStatThrottleRate 120
   RailsAutoDetect On
</IfModule>

<VirtualHost *:80>
   ServerName $(hostname)
   DocumentRoot $SOURCE_DIR/DrQueue-0.64.4c3/DrQueueOnRails/public/
   RailsEnv production
<Directory $SOURCE_DIR/DrQueue-0.64.4c3/DrQueueOnRails/public/>
   # This relaxes Apache security settings.
   AllowOverride all
   # MultiViews must be turned off.
   Options -MultiViews
</Directory>
   XSendFile on
   XSendFilePath $INSTALL_DIR/drqueue
   #XSendFileAllowAbove on
</VirtualHost>
_GEEK_
/etc/init.d/httpd start
chkconfig httpd on
yum -y install dnsmasq
chkconfig dnsmasq on
echo "nameserver $IPADDR" >> /etc/resolv.conf
/etc/init.d/dnsmasq start
source /etc/profile
nohup master > /dev/null 2>&1 &
killall master.Linux.x86_64
nohup master > /dev/null 2>&1 &
echo -e "source /etc/profile\nnohup master > /dev/null 2>&1 &" >> /etc/rc.local
